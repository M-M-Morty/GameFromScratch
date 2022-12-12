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
	//��ʼ����Ϸ
	bool Initialize();
	//ִ����Ϸѭ��ֱ����Ϸ����
	void RunLoop();
	//�ر���Ϸ
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() { return mRenderer; }
	class AudioSystem* GetAudioSystem() { return mAudioSystem; }
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }
	class HUD* GetHUD() { return mHUD; }

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


	//������������Ϸ�е�actor
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
	//��ʱ���漴����ӵ�mActor���е�actor
	std::vector<class Actor* > mPendingActors;

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;
	class PhysWorld* mPhysWorld;
	class HUD* mHUD;

	Uint32 mTicksCount;
	GameState mGameState;
	//��¼��ǰ�Ƿ��ڸ���actor
	bool mUpdatingActors;

	//�ض���Ϸ����
	class FollowActor* mFollowActor;
	std::vector<class PlaneActor*> mPlanes;
	class SpriteComponent* mCrosshair;
	SoundEvent mMusicEvent;	
};