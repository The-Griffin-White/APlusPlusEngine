#include "GameObjectExitCommand.h"
#include "GameObject.h"

#include "GameObjAttorneyToExitCommand.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* g)
	: ptrGb(g)
{
}

void GameObjectExitCommand::execute()
{
	GameObjAttorneyToExitCommand::SceneExit(ptrGb);
}