#include "Game.h"
#include "Actor.h"
#include "SDL/SDL_Image.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include <algorithm>
#include "Random.h"
#include "InputSystem.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"

Game::Game()
	:mWindow(nullptr)
	,mIsRunning(true)
	,mUpdatingActors(false)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 8)", 100, 100,
		1024, 768, SDL_WINDOW_OPENGL);
	// Initialize input system
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
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

void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			mInputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	mInputSystem->Update();
	const InputState& state = mInputSystem->GetState();
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE))
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	//等待直到距离上一帧16ms
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	//更新所有actor
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//将所有待定actor添加到mActors中
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//将所有dead actors添加到一个临时vector上
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	//删除所有死去的对象（从mActors移除这些对象的指针）
	for (auto actor : deadActors)
	{
		delete actor;
		actor = nullptr;
	}
}

void Game::GenerateOutput()
{
	// Set the clear color to grey
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw all sprite components
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set shader/vao as active
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	// Swap the buffers
	SDL_GL_SwapWindow(mWindow);
}

bool Game::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// Set the view-projection matrix
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void Game::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Game::LoadData()
{
	//创建并设置飞船
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.f, 384.f));
	mShip->SetRotation(Math::PiOver2);

	//创建
	const  int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

void Game::UnloadData()
{
	//清除actor
	//因为~Actor调用了RemoveActor,必须使用一个不同的循环风格
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	//清除贴图
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// 是否已经在贴图map中
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		//从文件中加载
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// 从surface创建贴图
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(),
		mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}


void Game::Shutdown()
{
	UnloadData();

	mInputSystem->Shutdown();
	delete mInputSystem;

	IMG_Quit();
	
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	//如果正在更新actor，则将新的actor添加到待定序列。
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
	//先从待定序列中查找该actor
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//与最后一个元素交换并从尾部弹出（避免可能的大范围复制）
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	 iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//与最后一个元素交换并从尾部弹出（避免可能的大范围复制，前提是容器中的元素是无序的）
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)//根据绘制顺序选择插入位置
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
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	//不可以交换弹出（因为mSprites容器中的元素是有序的）
	mSprites.erase(iter);
}




