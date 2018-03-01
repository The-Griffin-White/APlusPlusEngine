#ifndef _SceneAttorneyToGameObject
#define _SceneAttorneyToGameObject

#include "Scene.h"
#include "SceneManager.h"

class SceneRegistrationCommand;

class SceneAttorneyToGameObject
{
private:
	friend class GameObject;

	static void SubmitCommand(SceneRegistrationCommand* c)
	{
		SceneManager::Get()->SubmitCommand(c);
	};
};

#endif