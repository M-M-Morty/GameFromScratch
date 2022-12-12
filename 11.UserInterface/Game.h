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

	// Manage UI stack
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	void PushUI(class UIScreen* screen);

	class FPSActor* GetPlayer() { return mFPSActor; }

	enum GameState
	{
		EGameplay,
		EPaused,
		EQuit
	};

	GameState GetState() const { return mGameState; }
	void SetState(GameState state) { mGameState = state; }


	class Font* GetFont(const std::string& fileName);

	void LoadText(const std::string& fileName);
	const std::string& GetText(const std::string& key);

	//具体游戏的代码
	void AddPlane(class PlaneActor* plane);
	void RemovePlane(class PlaneActor* plane);
	std::vector<class PlaneActor*>& GetPlanes() { return mPlanes; }
private:
	void ProcessInput();
	void HandleKeyPress(int key);
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	//保存所有在游戏中的actor
	std::vector<class Actor*> mActors;
	std::vector<class UIScreen*> mUIStack;
	std::unordered_map<std::string, class Font*> mFonts;

	// Map for text localization
	std::unordered_map<std::string, std::string> mText;
	//暂时保存即将添加到mActor序列的actor
	std::vector<class Actor* > mPendingActors;

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;
	class PhysWorld* mPhysWorld;
	class HUD* mHUD;

	Uint32 mTicksCount;
	
	//记录当前是否在更新actor
	bool mUpdatingActors;
	GameState mGameState;
	//具体游戏的代码
	std::vector<class PlaneActor*> mPlanes;
	class FPSActor* mFPSActor;
	class SpriteComponent* mCrosshair;
	SoundEvent mMusicEvent;	
};