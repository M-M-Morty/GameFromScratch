#include "Game.h"
#include "Actor.h"
#include "SDL/SDL_Image.h"
#include "SpriteComponent.h"

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mIsRunning(true)
	,mUpdatingActors(false)
{

}


bool Game::Initialize()
{
	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image:%s", SDL_GetError());
		return false;
	}
}


void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}



void Game::AddActor(Actor* actor)
{
	//������ڸ���actor�����µ�actor��ӵ��������С�
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	
}

void Game::AddSprite(SpriteComponent* sprite)//���ݻ���˳��ѡ�����λ��
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if(myDrawOrder<(*iter)->GetDrawOrder())
			break;
	}
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	return nullptr;
}


void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	//�ȴ�ֱ��������һ֡16ms
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	//��������actor
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mTicksCount = false;

	//�����д���actor��ӵ�mActors��
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//������dead actors��ӵ�һ����ʱvector��
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	//ɾ��������ȥ�Ķ��󣨴�mActors�Ƴ���Щ�����ָ�룩
	for (auto actor : deadActors)
	{
		delete actor;
		actor = nullptr;
	}
}

void Game::LoadData()
{
}

void Game::UnloadData()
{
}
