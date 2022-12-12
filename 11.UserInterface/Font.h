#pragma once
#include <string>
#include <unordered_map>
#include <SDL/SDL_ttf.h>

#include "Math.h"

class Font
{
public:
	Font(class Game* game);
	~Font();
	//从文件中加载字体
	bool Load(const std::string& fileName);
	void Unload();

	class Texture* RenderText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
private:
	// 字体大小到字体数据的映射
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
};