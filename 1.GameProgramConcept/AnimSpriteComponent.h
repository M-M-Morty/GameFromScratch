#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent :public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	//ÿ֡���¶���,��д��component
	void Update(float deltaTime) override;
	//���ö���ÿһ֡����ͼ
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

	float GetAnimFPS() { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
	//���涯��ÿһ֡����ͼ
	std::vector<SDL_Texture*> mAnimTextures;
	//��ǰ֡
	float mCurrentFrame;
	//��������֡��
	float mAnimFPS;
};