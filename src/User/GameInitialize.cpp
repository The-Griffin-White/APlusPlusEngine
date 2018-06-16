#include "APlusPlusEngine.h"

#include "SceneManager.h"
#include "DemoScene.h"
#include "TestLevel.h"
#include "Level1.h"
#include "Level2.h"

void APlusPlusEngine::GameInitialize()
{
	this->setWindowName("A++ Engine Demo");
	this->setWidthHeight(1200, 900);
	this->SetClearColor(Colors::CadetBlue, 1.0f);
}

void APlusPlusEngine::ClearUserContent()
{
}

void APlusPlusEngine::SetStartScene()
{
	SceneManager::SetNextScene(new Level1);
}