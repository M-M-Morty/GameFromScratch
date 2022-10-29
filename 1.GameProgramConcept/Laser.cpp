#include "Laser.h"
#include "SpriteComponent.h"
#include "MovementComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(1.f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.f);
}

void Laser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.f)
	{
		SetState(EDead);
	}
	else
	{
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//若激光和小行星的圆形碰撞组件相交，设置激光和小行星为死亡状态，并结束循环
				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
}
