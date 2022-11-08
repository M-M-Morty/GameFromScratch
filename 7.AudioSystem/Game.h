#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>


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
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();


	//������������Ϸ�е�actor
	std::vector<class Actor*> mActors;
	//��ʱ���漴����ӵ�mActor���е�actor
	std::vector<class Actor* > mPendingActors;

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;
	class CameraActor* mCameraActor;

	Uint32 mTicksCount;
	bool mIsRunning;
	//��¼��ǰ�Ƿ��ڸ���actor
	bool mUpdatingActors;



	
};