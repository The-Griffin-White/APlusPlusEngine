#ifndef _SceneAttorneyToInputable
#define _SceneAttorneyToInputable

#include "Scene.h"
#include "SceneManager.h"

class SceneRegistrationCommand;

class SceneAttorneyToInputable
{
private:
	friend class Inputable;

	static void SubmitCommand(SceneRegistrationCommand* c)
	{
		SceneManager::Get()->SubmitCommand(c);
	};

	static void Register(Inputable* in, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
	{
		return SceneManager::Get()->RegisterInputable(in, k, e);
	};

	static void Deregister(Inputable* in, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
	{
		SceneManager::Get()->DeregisterInputable(in, k, e);
	};
};

#endif