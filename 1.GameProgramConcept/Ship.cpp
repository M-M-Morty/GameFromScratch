#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Laser.h"
#include "InputComponent.h"


Ship::Ship(class Game* game)
	:Actor(game)
	/*,mRightSpeed(0.0f)
	,mDownSpeed(0.0f)*/
	,mLaserCooldown(0.f)
{
	////��������sprite���
	//AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	//std::vector<SDL_Texture*> anim = {
	//	game->GetTexture("Assets/Ship01.png"),
	//	game->GetTexture("Assets/Ship02.png"),
	//	game->GetTexture("Assets/Ship03.png"),
	//	game->GetTexture("Assets/Ship04.png")
	//};
	//asc->SetAnimTextures(anim);
	//����sprite���
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime)
{
	//Actor::UpdateActor(deltaTime);
	////�����ٶȺ�����ʱ�����λ��
	//Vector2 pos = GetPosition();
	//pos.x += mRightSpeed * deltaTime;
	//pos.y += mRightSpeed * deltaTime;
	////����λ�õ������
	//if (pos.x < 25.0f)
	//{
	//	pos.x = 25.0f;
	//}
	//else if (pos.x > 500.f)
	//{
	//	pos.x = 500.f;
	//}
	//if (pos.y < 25.0f)
	//{
	//	pos.y = 25.0f;
	//}
	//else if (pos.y > 743.0f)
	//{
	//	pos.y = 743.0f;
	//}
	//SetPosition(pos);

	mLaserCooldown -= deltaTime;
}

//void Ship::ProcessKeyboard(const uint8_t* state)
//{
//	//����
//	if (state[SDL_SCANCODE_D])
//	{
//		mRightSpeed += 250.f;
//	}
//	if (state[SDL_SCANCODE_A])
//	{
//		mRightSpeed -= 250.f;
//	}
//	//����
//	if (state[SDL_SCANCODE_S])
//	{
//		mRightSpeed += 300.f;
//	}
//	if (state[SDL_SCANCODE_W])
//	{
//		mRightSpeed -= 250.f;
//	}
//}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		//���ⷢ��������ȴʱ��
		mLaserCooldown = 0.5f;
	}
}

