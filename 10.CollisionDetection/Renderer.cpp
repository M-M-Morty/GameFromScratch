#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <GL/glew.h>

Renderer::Renderer(Game* game)
    :mGame(game)
    ,mSpriteShader(nullptr)
    ,mMeshShader(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float screenWidth, float screeHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screeHeight;

	// 使用核心配置
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//设置版本为3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// 设置8bit的RGBA通道
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// 设置为双重缓冲
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// 强制使用硬件加速（GPU计算）
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Game Programming in C++ ", 100, 100,
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// 创建OpenGl上下文
	mContext = SDL_GL_CreateContext(mWindow);

	//初始化GLFW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	glGetError();

	// 加载着色器
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	//创建sprite顶点
	CreateSpriteVerts();

	return true;
}

void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	mMeshShader->Unload();
	delete mMeshShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnLoadData()
{
	// 清除贴图
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// 清除网格体
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::Draw()
{
	// 设置缓冲颜色为灰色
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// 应用颜色缓冲
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 绘制网格组件(3D)
	// 开启深度缓冲/取消颜色混合
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// 激活网格体着色器
	mMeshShader->SetActive();
	// 更新视图-投影变换
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// 更新光照Uniform
	SetLightUniforms(mMeshShader);
	for (auto mc : mMeshComps)
	{
		mc->Draw(mMeshShader);
	}

	// 绘制sprite组件(2D)
	// 禁用深度缓冲
	glDisable(GL_DEPTH_TEST);
	// 开启alpha颜色混合
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// 激活sprite着色器的VAO
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	//交换缓冲区
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	mMeshComps.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	Mesh* m = nullptr;
	auto iter = mMeshes.find(fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	else
	{
		m = new Mesh();
		if (m->Load(fileName, this))
		{
			mMeshes.emplace(fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

Vector3 Renderer::Unproject(const Vector3& screenPoint) const
{
	// Convert screenPoint to device coordinates (between -1 and +1)
	Vector3 deviceCoord = screenPoint;
	deviceCoord.x /= (mScreenWidth) * 0.5f;
	deviceCoord.y /= (mScreenHeight) * 0.5f;

	// Transform vector by unprojection matrix
	Matrix4 unprojection = mView * mProjection;
	unprojection.Invert();
	return Vector3::TransformWithPerspDiv(deviceCoord, unprojection);
}

void Renderer::GetScreenDirection(Vector3& outStart, Vector3& outDir) const
{
	// Get start point (in center of screen on near plane)
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	outStart = Unproject(screenPoint);
	// Get end point (in center of screen, between near and far)
	screenPoint.z = 0.9f;
	Vector3 end = Unproject(screenPoint);
	// Get direction vector
	outDir = end - outStart;
	outDir.Normalize();
}

bool Renderer::LoadShaders()
{
	// 创建sprite着色器
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// 设置视图-投影矩阵
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	//创建基础网格体
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
	{
		return false;
	}

	mMeshShader->SetActive();
	// 设置视图-投影矩阵
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		mScreenWidth, mScreenHeight, 25.0f, 10000.0f);
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	return true;
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader)
{
	// 摄像机位置来自转置的视图变换矩阵
	Matrix4 invView = mView;
	invView.Invert();
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	//环境光照rgb
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// 平行光
	shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.mDirection);
	shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.mDiffuseColor);
	shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.mSpecColor);
}
