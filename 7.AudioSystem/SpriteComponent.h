#pragma once

#include "Component.h"
#include "SDL/SDL.h"

class SpriteComponent : public Component
{
public:
	//drawOrder数字越小，绘制的时间就越晚
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);

	//getter函数
	int GetDrawOrder()const { return mDrawOrder; }
	int GetTexWidth()const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

protected:

	Texture* mTexture;
	int mDrawOrder;//为画家算法所用的绘制顺序值
	int mTexWidth;
	int mTexHeight;
};