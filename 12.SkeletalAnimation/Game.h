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


	//������������Ϸ�е�actor
	std::vector<class Actor*> mActors;
	//��ʱ���漴����ӵ�mActor���е�actor
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
	//��¼��ǰ�Ƿ��ڸ���actor
	bool mUpdatingActors;

	//�ض���Ϸ����
	std::vector<class PlaneActor*> mPlanes;
	class FPSActor* mFPSActor;
	class SpriteComponent* mCrosshair;
	SoundEvent mMusicEvent;	
};