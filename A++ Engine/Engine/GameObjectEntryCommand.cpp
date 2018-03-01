#include "GameObjectEntryCommand.h"
#include "GameObject.h"

#include "GameObjAttorneyToEntryCommand.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* g)
	: ptrGb(g)
{
}

void GameObjectEntryCommand::execute()
{
	GameObjAttorneyToEntryCommand::SceneEntry(ptrGb);
}