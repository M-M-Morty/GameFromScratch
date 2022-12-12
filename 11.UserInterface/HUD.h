#pragma once
#include "UIScreen.h"


class HUD :public UIScreen
{
public:
	HUD(class Game* game);
	~HUD();

	void Update(float deltaTime) override;
	void Draw(class Shader* shader) override;

	void AddTargetComponent(class TargetComponent* tc);
	void RemoveTargetComponent(class TargetComponent* tc);
protected:
	void UpdateCrosshair(float deltaTime);
	void UpdateRadar(float deltaTime);

	class Texture* mHealthBar;
	class Texture* mRadar;
	class Texture* mCrosshair;
	class Texture* mCrosshairEnemy;
	class Texture* mBlipTex;
	class Texture* mRadarArrow;

	// All the target components in the game
	std::vector<class TargetComponent*> mTargetComps;
	//光点相对于雷达零点的2D偏移量
	std::vector<Vector2> mBlips;
	// 调整雷达的搜寻范围和绘制半径
	float mRadarRange;
	float mRadarRadius;
	//瞄准的目标是否是敌人
	bool mTargetEnemy;
};