#pragma once


#include <vector>
#include <string>
#include "Collision.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	// ����/ж�������ļ�
	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();

	const AABB& GetBox() { return mBox; }
	// ���������Ķ�������
	class VertexArray* GetVertexArray() { return mVertexArray; }
	// ����������ȡ��Ӧ��ͼ
	class Texture* GetTexture(size_t index);
	// ��ȡshader����
	const std::string& GetShaderName() const { return mShaderName; }
	// ��ȡ����ռ��Χ��İ뾶
	float GetRadius() const { return mRadius; }
	//��ȡ�������߹�ǿ��
	float GetSpecPower() const { return mSpecPower; }
private:
	// AABB��ײ
	AABB mBox;
	// ���������йص���ͼ
	std::vector<class Texture*> mTextures;
	// ������Ķ�������
	class VertexArray* mVertexArray;
	// shader����
	std::string mShaderName;
	// ����ռ��Χ��İ뾶
	float mRadius;
	// ����߹�ǿ��
	float mSpecPower;
};
