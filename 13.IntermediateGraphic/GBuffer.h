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

	//��������G������
	bool Create(int width, int height);
	void Destroy();

	//��þ�������
	class Texture* GetTexture(Type type);
	//���֡��������ID
	unsigned int GetBufferID() const { return mBufferID; }
	//����������Ҫ������G-Buffer��ͼ
	void SetTexturesActive();
private:
	//��G���������������ͼ
	std::vector<class Texture*> mTextures;
	//֡��������ID
	unsigned int mBufferID;
};
