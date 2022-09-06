#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>

class Game
{
public:
	Game();
	bool Initialize();//��ʼ����Ϸ
	void RunLoop();//ִ����Ϸѭ��ֱ����Ϸ����
	void Shutdown();//�ر���Ϸ

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

	std::vector<class Actor*> mActors;//������������Ϸ�е�actor
	std::vector<class Actor* > mPendingActors;//��ʱ���漴����ӵ�mActor���е�actor
	std::vector<class SpriteComponent*> mSprites;//��������Ƶľ���


	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;//��¼��ǰ�Ƿ��ڸ���actor
};