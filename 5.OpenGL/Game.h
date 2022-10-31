#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>


class Game
{
public:
	Game();
	bool Initialize();//初始化游戏
	void RunLoop();//执行游戏循环直到游戏结束
	void Shutdown();//关闭游戏

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	
	class Texture* GetTexture(const std::string& fileName);

	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	void CreateSpriteVerts();
	void LoadData();
	void UnloadData();

	//保存加载的地图
	std::unordered_map<std::string, Texture*> mTextures;
	//保存所有在游戏中的actor
	std::vector<class Actor*> mActors;
	//暂时保存即将添加到mActor序列的actor
	std::vector<class Actor* > mPendingActors;
	//保存需绘制的精灵
	std::vector<class SpriteComponent*> mSprites;
	//sprite着色器
	class Shader* mSpriteShader;
	// Sprit的顶点数组
	class VertexArray* mSpriteVerts;


	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTicksCount;
	bool mIsRunning;
	//记录当前是否在更新actor
	bool mUpdatingActors;

	//特定游戏的成员变量
	class Ship* mShip;
	std::vector<class Asteroid*> mAsteroids;
};