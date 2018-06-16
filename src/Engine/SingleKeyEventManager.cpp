#include "SingleKeyEventManager.h"

#include "InputableAttorneyToSKManager.h"

#include <assert.h>

SingleKeyEventManager::SingleKeyEventManager()
{
	// Shouldn't hit this...
	assert(0);
	key = APPE_KEY::KEY_0;
}

SingleKeyEventManager::SingleKeyEventManager(APPE_KEY k)
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

SingleKeyEventManager::KeyMgrRef SingleKeyEventManager::Register(Inputable* p, Inputable::INPUT_EVENT_TYPE e)
{
	if (e == Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	{
		return keyPressCol.insert(keyPressCol.begin(), p);
	}
	else
	{
		return keyReleaseCol.insert(keyReleaseCol.begin(), p);
	}
}
void SingleKeyEventManager::Deregister(Inputable::KeyMgrRef keyRef, Inputable::INPUT_EVENT_TYPE e)
{
	if (e == Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	{
		keyPressCol.erase(keyRef);
	}
	else
	{
		keyReleaseCol.erase(keyRef);
	}
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	if (Keyboard::IsKeyActive(key))
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