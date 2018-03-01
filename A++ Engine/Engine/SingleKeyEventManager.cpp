#include "SingleKeyEventManager.h"

#include "InputableAttorneyToSKManager.h"

#include <assert.h>

SingleKeyEventManager::SingleKeyEventManager()
{
	// Shouldn't hit this...
	assert(0);
	key = AZUL_KEY::KEY_0;
}

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
{
	key = k;
}

SingleKeyEventManager::~SingleKeyEventManager()
{
	DebugMsg::out("SingleKeyEventManager deleted\n");
	auto itr = keyPressCol.begin();
	while (!keyPressCol.empty())
	{
		keyPressCol.erase(itr++);
	}
	itr = keyReleaseCol.begin();
	while (!keyReleaseCol.empty())
	{
		keyReleaseCol.erase(itr++);
	}
}

void SingleKeyEventManager::Register(Inputable* p, Inputable::INPUT_EVENT_TYPE e)
{
	if (e == Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	{
		keyPressCol.insert(keyPressCol.begin(), p);
	}
	else
	{
		keyReleaseCol.insert(keyReleaseCol.begin(), p);
	}
}
void SingleKeyEventManager::Deregister(Inputable* p, Inputable::INPUT_EVENT_TYPE e)
{
	if (e == Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	{
		keyPressCol.remove(p);
	}
	else
	{
		keyReleaseCol.remove(p);
	}
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	if (Keyboard::GetKeyState(key))
	{
		for (auto itr = keyPressCol.begin(); itr != keyPressCol.end(); ++itr)
		{
			InputableAttorneyToSKManager::KeyPressed(*itr, key);
		}
	}
	else
	{
		for (auto itr = keyReleaseCol.begin(); itr != keyReleaseCol.end(); ++itr)
		{
			InputableAttorneyToSKManager::KeyReleased(*itr, key);
		}
	}
}