#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	// ���������Ĵ�С�������ž���
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(mTexWidth),
		static_cast<float>(mTexHeight),
		1.0f);

	Matrix4 world = scaleMat * mOwner->GetWorldTransform();

	// ����ģ�ͱ任����
	shader->SetMatrixUniform("uWorldTransform", world);
	//���õ�ǰ��ͼ
	mTexture->SetActive();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	//��ѯ��ͼ�ĸ߶ȺͿ��������ó�Ա����
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}