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

	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	void CreateSpriteVerts();
	void LoadData();
	void UnloadData();

	//������صĵ�ͼ
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	//������������Ϸ�е�actor
	std::vector<class Actor*> mActors;

	class InputSystem* mInputSystem;

	//��ʱ���漴����ӵ�mActor���е�actor
	std::vector<class Actor* > mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	// Sprite ��ɫ��
	class Shader* mSpriteShader;
	// Sprite ��������
	class VertexArray* mSpriteVerts;


	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;//��¼��ǰ�Ƿ��ڸ���actor

	//�ض���Ϸ�ĳ�Ա����
	class Ship* mShip;
	std::vector<class Asteroid*> mAsteroids;
};