#pragma once
#include <GL/glew.h>

class VertexArray
{
public:
	VertexArray(const float* verts,unsigned int numVerts,
				const unsigned int* indices,unsigned int numIndices);
	~VertexArray();

	//激活顶点数组（之后就可以绘制）
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

private:
	// 顶点缓冲中顶点的数量
	unsigned int mNumVerts;
	// 索引缓冲中索引的数量
	unsigned int mNumIndices;
	// 顶点缓冲的引用（ID）
	unsigned int mVertexBuffer;
	//索引缓冲的引用（ID）
	unsigned int mIndexBuffer;
	// 顶点数组对象（顶点布局）的引用（ID）
	unsigned int mVertexArray;
 };
