#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "SoundEvent.h"

class Renderer;

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
	class AudioSystem* GetAudioSystem() { return mAudioSystem; }
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }

	// Game-specific
	void AddPlane(class PlaneActor* plane);
	void RemovePlane(class PlaneActor* plane);
	std::vector<class PlaneActor*>& GetPlanes() { return mPlanes; }

	enum GameState
	{
		EGameplay,
		EPaused,
		EQuit
	};

	GameState GetState() const { return mGameState; }
	void SetState(GameState state) { mGameState = state; }
private:
	void ProcessInput();
	void HandleKeyPress(int key);
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();


	//保存所有在游戏中的actor
	std::vector<class Actor*> mActors;
	//暂时保存即将添加到mActor序列的actor
	std::vector<class Actor* > mPendingActors;


	// Map of loaded skeletons
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// Map of loaded animations
	std::unordered_map<std::string, class Animation*> mAnims;

	

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;
	class PhysWorld* mPhysWorld;

	Uint32 mTicksCount;
	GameState mGameState;
	//记录当前是否在更新actor
	bool mUpdatingActors;

	//特定游戏代码
	std::vector<class PlaneActor*> mPlanes;
	class FPSActor* mFPSActor;
	class SpriteComponent* mCrosshair;
	SoundEvent mMusicEvent;	
};