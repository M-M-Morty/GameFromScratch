#pragma once


#include <vector>
#include <string>

class Mesh
{
public:
	Mesh();
	~Mesh();
	// 加载/卸载网格文件
	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	// 获得网格体的顶点数组
	class VertexArray* GetVertexArray() { return mVertexArray; }
	// 根据索引获取对应贴图
	class Texture* GetTexture(size_t index);
	// 获取shader名字
	const std::string& GetShaderName() const { return mShaderName; }
	// 获取物体空间包围球的半径
	float GetRadius() const { return mRadius; }
	//获取物体表面高光强度
	float GetSpecPower() const { return mSpecPower; }
private:
	// 与网格体有关的贴图
	std::vector<class Texture*> mTextures;
	// 网格体的顶点数组
	class VertexArray* mVertexArray;
	// shader名字
	std::string mShaderName;
	// 物体空间包围球的半径
	float mRadius;
	// 表面高光强度
	float mSpecPower;
};
