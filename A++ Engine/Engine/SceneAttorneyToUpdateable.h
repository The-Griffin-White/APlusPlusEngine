#ifndef _SceneAttorneyToUpdateable
#define _SceneAttorneyToUpdateable

#include "Scene.h"
#include "SceneManager.h"

class SceneRegistrationCommand;

class SceneAttorneyToUpdateable
{
private:
	friend class Updateable;

	static void SubmitCommand(SceneRegistrationCommand* c) 
	{ 
		SceneManager::Get()->SubmitCommand(c); 
	};

	static UpdateableManager::UpdateableListRef Register(Updateable* up)
	{ 
		return SceneManager::Get()->RegisterUpdateable(up); 
	};

	static void Deregister(UpdateableManager::UpdateableListRef itr) 
	{ 
		SceneManager::Get()->DeregisterUpdateable(itr); 
	};
};

#endif