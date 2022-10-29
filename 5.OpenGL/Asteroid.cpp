#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MovementComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	//设置随机位置和旋转
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.f, Math::TwoPi));

	//创建sprite组件
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//创建移动组件，并设置移动速度
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);

	//创建圆形组件(碰撞计算)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.f);

	//将当前asteroid实例添加到游戏实例中
	game->AddAsteroid(this);

}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
