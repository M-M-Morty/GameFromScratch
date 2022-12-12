#include "VertexArray.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, Layout layout,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts), mNumIndices(numIndices)
{
	//创建顶点数组
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	unsigned vertexSize = 8 * sizeof(float);
	if (layout == PosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}

	//创建顶点缓冲
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 3 * sizeof(float), verts, GL_STATIC_DRAW);
	//创建索引缓冲
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	if (layout == PosNormTex)
	{
		//设置顶点位置属性
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		//设置顶点法向量属性
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
			reinterpret_cast<void*>(sizeof(float) * 3));
		//设置顶点纹理坐标属性
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (layout == PosNormSkinTex)
	{
		// Position is 3 floats
			glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// Normal is 3 floats
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// Skinning indices (keep as ints)
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
		// Skinning weights (convert to floats)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		// Texture coordinates
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
	
	

}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mVertexBuffer);
	glGenVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
