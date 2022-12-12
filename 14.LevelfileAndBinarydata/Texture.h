#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	void Unload();

	void CreateForRendering(int width, int height, unsigned int format);

	void SetActive(int index);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	unsigned int GetTextureID() const { return mTextureID; }
private:
	// OpenGL ID of this texture
	unsigned int mTextureID;
	// Width/height of the texture
	int mWidth;
	int mHeight;
};
