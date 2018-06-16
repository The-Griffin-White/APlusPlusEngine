#include "Player.h"
#include "SceneManager.h"
#include "Level1.h"
#include "Tank.h"
#include "TextureManager.h"
#include "SpriteFactory.h"
#include "Sprite.h"

Player::Player()
{
	lifeSprites = new Sprite*[3];
	lifeSprites[0] = SpriteFactory::CreateSprite(TextureManager::Get("Life"), new Rect(0, 0, 100.0f, 100.0f));
	lifeSprites[0]->Pos(100.0f, 100.0f);
	lifeSprites[1] = SpriteFactory::CreateSprite(TextureManager::Get("Life"), new Rect(0, 0, 100.0f, 100.0f));
	lifeSprites[1]->Pos(200.0f, 100.0f);
	lifeSprites[2] = SpriteFactory::CreateSprite(TextureManager::Get("Life"), new Rect(0, 0, 100.0f, 100.0f));
	lifeSprites[2]->Pos(300.0f, 100.0f);
	pTank = new Tank;
	lives = 3;
}

Player::~Player()
{
	delete pTank;
	delete lifeSprites[0];
	delete lifeSprites[1];
	delete lifeSprites[2];
	delete[] lifeSprites;
}

void Player::DecrementLives()
{
	this->RemoveTank();
	--lives;
	if (lives <= 0)
		this->ResetGame();
	else
		pTank->SetRespawnAlarm();
}

void Player::ResetGame()
{
	lives = 3;
	SceneManager::SetNextScene(new Level1);
}

void Player::SpawnTank()
{
	pTank->Initialize(Vect(1000, 1, 0));
	for (int i = 0; i < lives; ++i)
	{
		lifeSprites[i]->SubmitRegistration();
	}
}

void Player::RemoveTank()
{
	pTank->SubmitExit();
	for (int i = 0; i < lives; ++i)
	{
		lifeSprites[i]->SubmitDeregistration();
	}
}