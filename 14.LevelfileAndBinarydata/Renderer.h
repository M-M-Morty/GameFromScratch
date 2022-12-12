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
	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	void AddPointLight(class PointLightComponent* light);
	void RemovePointLight(class PointLightComponent* light);

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
	// Gets start point and direction of screen vector
	void GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	void SetMirrorView(const Matrix4& view) { mMirrorView = view; }
	class Texture* GetMirrorTexture() { return mMirrorTexture; }
private:
	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
		float viewPortScale = 1.0f, bool lit = true);
	bool CreateMirrorTarget();
	void DrawFromGBuffer();

	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader, const Matrix4& view);

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

	// 光照数据
	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	// 窗口
	SDL_Window* mWindow;
	// OpenGL上下文
	SDL_GLContext mContext;
	// 屏幕长宽
	float mScreenWidth;
	float mScreenHeight;

	unsigned int mMirrorBuffer;
	class Texture* mMirrorTexture;
	Matrix4 mMirrorView;

	class GBuffer* mGBuffer;
	// GBuffer shader
	class Shader* mGGlobalShader;
	class Shader* mGPointLightShader;
	std::vector<class PointLightComponent*> mPointLights;
	class Mesh* mPointLightMesh;
};