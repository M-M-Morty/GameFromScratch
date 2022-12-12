#pragma once
#include <vector>

class GBuffer
{
public:
	enum Type
	{
		EDiffuse = 0,
		ENormal,
		EWorldPos,
		NUM_GBUFFER_TEXTURES
	};

	GBuffer();
	~GBuffer();

	//创建销毁G缓冲区
	bool Create(int width, int height);
	void Destroy();

	//获得具体类型
	class Texture* GetTexture(Type type);
	//获得帧缓冲对象的ID
	unsigned int GetBufferID() const { return mBufferID; }
	//激活所有需要采样的G-Buffer贴图
	void SetTexturesActive();
private:
	//与G缓冲区相关联的贴图
	std::vector<class Texture*> mTextures;
	//帧缓冲对象的ID
	unsigned int mBufferID;
};
