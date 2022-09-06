#pragma once
#include "SpriteComponent.h"

class BGSpriteComponent :public SpriteComponent
{
public:
	//����Ĭ�ϵĻ���˳��ܵͣ������Ǳ�����
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	//��д���Ը����Update��Draw�麯��
	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer) override;
	//�������ڱ�������ͼ��
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	//������װÿ��������ͼ������ƫ��ֵ
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

/* BGTexture �ṹ�彫ÿ����������������Ӧ��ƫ�����������
ÿһ֡����ƫ�������и��£��Դ�������Ч����
��Ҫ�ڴ����е�SetBGTextures�������ʼ��ƫ��������ÿ��������λ��ǰһ���������Ҳࡣ
*/