#ifndef _SceneAttorneyToCollidable
#define _SceneAttorneyToCollidable

#include "Scene.h"
#include "SceneManager.h"

class SceneRegistrationCommand;

class SceneAttorneyToCollidable
{
private:
	friend class Collidable;

	static void SubmitCommand(SceneRegistrationCommand* c)
	{
		SceneManager::Get()->SubmitCommand(c);
	};
};

#endif