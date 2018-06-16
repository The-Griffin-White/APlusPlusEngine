#include "PlayerManager.h"
#include "Player.h"

PlayerManager* PlayerManager::ptrInstance = nullptr;

PlayerManager::PlayerManager()
{
	pPlay = new Player;
}

PlayerManager::~PlayerManager()
{
	delete pPlay;
}

void PlayerManager::DecrementLives()
{
	Instance().pPlay->DecrementLives();
}
void PlayerManager::ResetGame()
{
	Instance().pPlay->ResetGame();
}
void PlayerManager::SpawnTank()
{
	Instance().pPlay->SpawnTank();
}
void PlayerManager::RemoveTank()
{
	Instance().pPlay->RemoveTank();
}

void PlayerManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}