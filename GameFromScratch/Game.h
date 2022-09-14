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
	
	SDL_Texture* GetTexture(const std::string& fileName);
private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	//保存加载的地图
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//保存所有在游戏中的actor
	std::vector<class Actor*> mActors;

	//暂时保存即将添加到mActor序列的actor
	std::vector<class Actor* > mPendingActors;

	//保存需绘制的精灵
	std::vector<class SpriteComponent*> mSprites;


	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;//记录当前是否在更新actor

	//飞船游戏独有的变量
	class Ship* mShip;
};