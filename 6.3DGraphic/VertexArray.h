#pragma once
#include <GL/glew.h>

class VertexArray
{
public:
	VertexArray(const float* verts,unsigned int numVerts,
				const unsigned int* indices,unsigned int numIndices);
	~VertexArray();

	//��������飨֮��Ϳ��Ի��ƣ�
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

private:
	// ���㻺���ж��������
	unsigned int mNumVerts;
	// ��������������������
	unsigned int mNumIndices;
	// ���㻺������ã�ID��
	unsigned int mVertexBuffer;
	//������������ã�ID��
	unsigned int mIndexBuffer;
	// ����������󣨶��㲼�֣������ã�ID��
	unsigned int mVertexArray;
 };
