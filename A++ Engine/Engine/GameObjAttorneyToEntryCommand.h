#ifndef _GameObjAttorneyToEntryCommand
#define _GameObjAttorneyToEntryCommand

#include "GameObject.h"

class GameObjAttorneyToEntryCommand
{
private:
	friend class GameObjectEntryCommand;
	static void SceneEntry(GameObject* al)
	{
		al->ConnectToScene();
	};
};

#endif