#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent :public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	//每帧更新动画,重写自component
	void Update(float deltaTime) override;
	//设置动画每一帧的贴图
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

	float GetAnimFPS() { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
	//保存动画每一帧的贴图
	std::vector<SDL_Texture*> mAnimTextures;
	//当前帧
	float mCurrentFrame;
	//动画更新帧率
	float mAnimFPS;
};