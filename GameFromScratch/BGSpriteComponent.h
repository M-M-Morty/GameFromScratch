#pragma once
#include "SpriteComponent.h"

class BGSpriteComponent :public SpriteComponent
{
public:
	//设置默认的绘制顺序很低（所以是背景）
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	//重写来自父类的Update和Draw虚函数
	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer) override;
	//设置用于背景的贴图集
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	//用来封装每个背景贴图和它的偏移值
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

/* BGTexture 结构体将每个背景纹理与其相应的偏移量相关联。
每一帧都对偏移量进行更新，以创建滚动效果。
需要在代码中的SetBGTextures函数里初始化偏移量，将每个背景定位在前一个背景的右侧。
*/