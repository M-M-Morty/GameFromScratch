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
	//���������״�����2Dƫ����
	std::vector<Vector2> mBlips;
	// �����״����Ѱ��Χ�ͻ��ư뾶
	float mRadarRange;
	float mRadarRadius;
	//��׼��Ŀ���Ƿ��ǵ���
	bool mTargetEnemy;
};