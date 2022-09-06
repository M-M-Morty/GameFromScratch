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
		//����֡�ʺ�����ʱ����µ�ǰ֡
		mCurrentFrame += mAnimFPS * deltaTime;

		//ѭ�����µ�ǰ֡
		while (mCurrentFrame >= mAnimTextures.size())
		{
			mCurrentFrame -= mAnimTextures.size();
		}
		//���ݵ�ǰ֡���õ�ǰ��ͼ
		SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		//����Ĭ�ϣ���0֡������ͼ
		mCurrentFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
