#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL/SDL.h>
#include "Math.h"

struct DirectionalLight
{
	// 平行光方向
	Vector3 mDirection;
	//漫反射颜色
	Vector3 mDiffuseColor;
	// 高光颜色
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize(float screenWidth, float screeHeight);
	void Shutdown();
	void UnLoadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);

	void SetViewMatrix(const Matrix4& view) { mView = view; }

	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	// Given a screen space point, unprojects it into world space,
	// based on the current 3D view/projection matrices
	// Expected ranges:
	// x = [-screenWidth/2, +screenWidth/2]
	// y = [-screenHeight/2, +screenHeight/2]
	// z = [0, 1) -- 0 is closer to camera, 1 is further
	Vector3 Unproject(const Vector3& screenPoint) const;
	void GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }
private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader);

	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshes;

	std::vector<class SpriteComponent*> mSprites;

	std::vector<class MeshComponent*> mMeshComps;
	std::vector<class SkeletalMeshComponent*> mSkeletalMeshes;

	class Game* mGame;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;

	class Shader* mMeshShader;
	class Shader* mSkinnedShader;

	Matrix4 mView;
	Matrix4 mProjection;
	// 屏幕长宽
	float mScreenWidth;
	float mScreenHeight;

	// 光照数据
	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	// 窗口
	SDL_Window* mWindow;
	// OpenGL上下文
	SDL_GLContext mContext;
};