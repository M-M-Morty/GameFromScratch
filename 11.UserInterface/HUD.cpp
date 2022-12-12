#include "HUD.h"
#include "Texture.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "PhysWorld.h"
#include "FPSActor.h"
#include <algorithm>
#include "TargetComponent.h"

HUD::HUD(Game* game)
	:UIScreen(game)
{
}

HUD::~HUD()
{
}

void HUD::Update(float deltaTime)
{
}

void HUD::Draw(Shader* shader)
{
	//绘制准星
	Texture* cross = mTargetEnemy ? mCrosshairEnemy : mCrosshair;
	DrawTexture(shader, cross, Vector2::Zero, 2.f);
	//绘制雷达
	const Vector2 cRadarPos(-390.0f, 275.0f);
	DrawTexture(shader, mRadar, cRadarPos, 1.0f);
	//绘制雷达上的光点
	for (auto& blip : mBlips)
	{
		DrawTexture(shader, mBlipTex, cRadarPos + blip, 1.0f);
	}
}

void HUD::AddTargetComponent(TargetComponent* tc)
{
	mTargetComps.emplace_back(tc);
}

void HUD::RemoveTargetComponent(TargetComponent* tc)
{
	auto iter = std::find(mTargetComps.begin(), mTargetComps.end(),tc);
	mTargetComps.erase(iter);
}

void HUD::UpdateCrosshair(float deltaTime)
{
	// Reset to regular cursor
	mTargetEnemy = false;
	// Make a line segment
	const float cAimDist = 5000.0f;
	Vector3 start, dir;
	mGame->GetRenderer()->GetScreenDirection(start, dir);
	LineSegment l(start, start + dir * cAimDist);
	// Segment cast
	PhysWorld::CollisionInfo info;
	if (mGame->GetPhysWorld()->SegmentCast(l, info))
	{
		// Is this a target?
		for (auto tc : mTargetComps)
		{
			if (tc->GetOwner() == info.mActor)
			{
				mTargetEnemy = true;
				break;
			}
		}
	}

}

void HUD::UpdateRadar(float deltaTime)
{
	//清除上一帧的光点位置
	mBlips.clear();

	// Convert player position to radar coordinates (x forward, z up)
	Vector3 playerPos = mGame->GetPlayer()->GetPosition();
	Vector2 playerPos2D = Vector2(playerPos.y, playerPos.x);
	// Ditto for player forward
	Vector3 playerForward = mGame->GetPlayer()->GetForward();
	Vector2 playerForward2D(playerForward.x, playerForward.y);

	// Use atan2 to get rotation of radar
	float angle = Math::Atan2(playerForward2D.y, playerForward2D.x);
	// Make a 2D rotation matrix
	Matrix3 rotMat = Matrix3::CreateRotation(angle);

	for (auto tc : mTargetComps)
	{
		Vector3 targetPos = tc->GetOwner()->GetPosition();
		Vector2 actorPos2D(targetPos.y, targetPos.x);

		// Calculate vector between player and target
		Vector2 playerToTarget = actorPos2D - playerPos2D;

		if (playerToTarget.LengthSq() <= (mRadarRange * mRadarRange))
		{
			// Convert playerToTarget into an offset from
			// the center of the on-screen radar
			Vector2 blipPos = playerToTarget;
			blipPos *= mRadarRadius / mRadarRange;

			// Rotate blipPos
			blipPos = Vector2::Transform(blipPos, rotMat);
			mBlips.emplace_back(blipPos);
		}
	}
}
