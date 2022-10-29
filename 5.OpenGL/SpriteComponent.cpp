#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Texture.h"

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

void SpriteComponent::Draw(Shader* shader)
{
	// 根据纹理的大小创建缩放矩阵
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(mTexWidth),
		static_cast<float>(mTexHeight),
		1.0f);

	Matrix4 world = scaleMat * mOwner->GetWorldTransform();

	// 设置模型变换矩阵
	shader->SetMatrixUniform("uWorldTransform", world);
	//设置当前贴图
	mTexture->SetActive();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	//查询贴图的高度和宽度以设置成员变量
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}
