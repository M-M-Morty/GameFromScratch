#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>


class Game
{
public:
	Game();
	//初始化游戏
	bool Initialize();
	//执行游戏循环直到游戏结束
	void RunLoop();
	//关闭游戏
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() { return mRenderer; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();


	//保存所有在游戏中的actor
	std::vector<class Actor*> mActors;
	//暂时保存即将添加到mActor序列的actor
	std::vector<class Actor* > mPendingActors;

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;
	class CameraActor* mCameraActor;

	Uint32 mTicksCount;
	bool mIsRunning;
	//记录当前是否在更新actor
	bool mUpdatingActors;



	
};