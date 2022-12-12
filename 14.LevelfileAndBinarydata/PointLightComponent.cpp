#include "PointLightComponent.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "Actor.h"

PointLightComponent::PointLightComponent(Actor* owner)
	:Component(owner)
{
	owner->GetGame()->GetRenderer()->AddPointLight(this);
}

PointLightComponent::~PointLightComponent()
{
	mOwner->GetGame()->GetRenderer()->RemovePointLight(this);
}

void PointLightComponent::Draw(Shader* shader, Mesh* mesh)
{
	// World transform is scaled to the outer radius (divided by the mesh radius)
	// and positioned to the world position
	Matrix4 scale = Matrix4::CreateScale(mOwner->GetScale() * mOuterRadius / mesh->GetRadius());
	Matrix4 trans = Matrix4::CreateTranslation(mOwner->GetPosition());
	Matrix4 worldTransform = scale * trans;
	shader->SetMatrixUniform("uWorldTransform", worldTransform);
	//设置点光源着色器常量
	shader->SetVectorUniform("uPointLight.mWorldPos", mOwner->GetPosition());
	shader->SetVectorUniform("uPointLight.mDiffuseColor", mDiffuseColor);
	shader->SetFloatUniform("uPointLight.mInnerRadius", mInnerRadius);
	shader->SetFloatUniform("uPointLight.mOuterRadius", mOuterRadius);

	//绘制球体
	glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetNumIndices(),
		GL_UNSIGNED_INT, nullptr);
}
