#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		//����ӵ���ߵ�scaleֵ�����Ż��ƾ��εĸ߶ȺͿ��
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		//actorλ��������������λ�ã�����Ⱦ�����ε�λ�������������Ͻǡ�
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);


		SDL_RenderCopyEx(
			renderer,
			mTexture,//Ҫ���Ƶ���ͼ
			nullptr,
			&r,		//Ŀ�곤����
			-Math::ToDegrees(mOwner->GetRotation()),//������ת�Ƕ�ֵ����������ͬ
			nullptr,
			SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//��ѯ��ͼ�ĸ߶ȺͿ�������ó�Ա����
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
