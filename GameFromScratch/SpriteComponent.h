#pragma once

#include "Component.h"

class SpriteComponent : public Component
{
public:
	//drawOrder����ԽС�����Ƶ�ʱ���Խ��
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	//getter����
	int GetDrawOrder()const { return mDrawOrder; }
	int GetTexWidth()const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

protected:

	SDL_Texture* mTexture;
	int mDrawOrder;//Ϊ�����㷨���õĻ���˳��ֵ
	int mTexWidth;
	int mTexHeight;
};