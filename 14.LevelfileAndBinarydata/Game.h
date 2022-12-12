#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "SoundEvent.h"

class Renderer;
class AudioSystem;
class PhysWorld;
class HUD;

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

	Renderer* GetRenderer() { return mRenderer; }
	AudioSystem* GetAudioSystem() { return mAudioSystem; }
	PhysWorld* GetPhysWorld() { return mPhysWorld; }
	HUD* GetHUD() { return mHUD; }

	// Manage UI stack
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	void PushUI(class UIScreen* screen);

	class FollowActor* GetPlayer() { return mFollowActor; }

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

	class Skeleton* GetSkeleton(const std::string& fileName);

	class Animation* GetAnimation(const std::string& fileName);
	// Game-specific
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
	// Map for fonts
	std::unordered_map<std::string, class Font*> mFonts;
	// Map of loaded skeletons
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// Map of loaded animations
	std::unordered_map<std::string, class Animation*> mAnims;

	// Map for text localization
	std::unordered_map<std::string, std::string> mText;
	//暂时保存即将添加到mActor序列的actor
	std::vector<class Actor* > mPendingActors;

	Renderer* mRenderer;
	AudioSystem* mAudioSystem;
	PhysWorld* mPhysWorld;
	HUD* mHUD;

	Uint32 mTicksCount;
	GameState mGameState;
	//记录当前是否在更新actor
	bool mUpdatingActors;

	//特定游戏代码
	class FollowActor* mFollowActor;
	std::vector<class PlaneActor*> mPlanes;
	class SpriteComponent* mCrosshair;
	SoundEvent mMusicEvent;	
};