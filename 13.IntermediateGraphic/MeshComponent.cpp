#include "MeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(Actor* owner, bool isSkeletal = false)
	:Component(owner)
	,mMesh(nullptr)
	,mTextureIndex(0)
	,mIsSkeletal(isSkeletal)
{
	mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{
	//����ģ�ͱ任
	shader->SetMatrixUniform("uWorldTransform", mOwner -> GetWorldTransform());
	//���ø߹�ǿ�ȱ任
	shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
	Texture* t = mMesh->GetTexture(mTextureIndex);
	if (t)
	{
		t->SetActive();
	}
	VertexArray* va = mMesh->GetVertexArray();
	va->SetActive();
	glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

