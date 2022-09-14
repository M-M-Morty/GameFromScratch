#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>


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

	//������صĵ�ͼ
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//������������Ϸ�е�actor
	std::vector<class Actor*> mActors;

	//��ʱ���漴����ӵ�mActor���е�actor
	std::vector<class Actor* > mPendingActors;

	//��������Ƶľ���
	std::vector<class SpriteComponent*> mSprites;


	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;//��¼��ǰ�Ƿ��ڸ���actor

	//�ɴ���Ϸ���еı���
	class Ship* mShip;
};