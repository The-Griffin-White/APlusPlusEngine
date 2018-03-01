#ifndef _SceneAttorneyToDrawable
#define _SceneAttorneyToDrawable

#include "Scene.h"
#include "SceneManager.h"

class SceneRegistrationCommand;

class SceneAttorneyToDrawable
{
private:
	friend class Drawable;

	static void SubmitCommand(SceneRegistrationCommand* c)
	{
		SceneManager::Get()->SubmitCommand(c);
	};

	static DrawableManager::DrawableListRef Register(Drawable* dr)
	{
		return SceneManager::Get()->RegisterDrawable(dr);
	};

	static void Deregister(DrawableManager::DrawableListRef itr)
	{
		SceneManager::Get()->DeregisterDrawable(itr);
	};
};

#endif