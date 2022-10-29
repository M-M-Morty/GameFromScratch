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
	//�������λ�ú���ת
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.f, Math::TwoPi));

	//����sprite���
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//�����ƶ�������������ƶ��ٶ�
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);

	//����Բ�����(��ײ����)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.f);

	//����ǰasteroidʵ����ӵ���Ϸʵ����
	game->AddAsteroid(this);

}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
