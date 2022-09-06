#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner,drawOrder)
	,mCurrentFrame(0)
	,mAnimFPS(24.f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		//根据帧率和增量时间更新当前帧
		mCurrentFrame += mAnimFPS * deltaTime;

		//循环更新当前帧
		while (mCurrentFrame >= mAnimTextures.size())
		{
			mCurrentFrame -= mAnimTextures.size();
		}
		//根据当前帧设置当前贴图
		SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		//设置默认（第0帧）的贴图
		mCurrentFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
