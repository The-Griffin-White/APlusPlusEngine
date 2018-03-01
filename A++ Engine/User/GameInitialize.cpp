#include "../Engine/APlusPlusEngine.h"

#include "../Engine/SceneManager.h"
#include "Level1.h"
#include "MovementDemoScene.h"

#include "BombFactory.h"
#include "EnemyTankFactory.h"

void APlusPlusEngine::GameInitialize()
{
	this->setWindowName("A++ Engine Demo");
	this->setWidthHeight(1200, 900);
	this->SetClearColor(Colors::CadetBlue, 1.0f);
}

void APlusPlusEngine::ClearUserContent()
{
	BombFactory::Terminate();
	EnemyTankFactory::Terminate();
}

void APlusPlusEngine::SetStartScene()
{
	SceneManager::SetNextScene(new Level1);
}