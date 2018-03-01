#ifndef _GameObjAttorneyToExitCommand
#define _GameObjAttorneyToExitCommand

#include "GameObject.h"

class GameObjAttorneyToExitCommand
{
private:
	friend class GameObjectExitCommand;
	static void SceneExit(GameObject* al)
	{
		al->DisconnectToScene();
	};
};

#endif