#include "KeyboardEventManager.h"

#include "SingleKeyEventManager.h"

#include <assert.h>

KeyboardEventManager::~KeyboardEventManager()
{
	DebugMsg::out("KeyboardEventManager deleted\n");
	auto itr = mapSKMgrs.begin();
	while (!mapSKMgrs.empty())
	{
		delete (itr->second);
		mapSKMgrs.erase(itr++);
	}
}

void KeyboardEventManager::Register(Inputable* p, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	auto itr = mapSKMgrs.find(k);
	if (itr != mapSKMgrs.end())
	{
		itr->second->Register(p, e);
	}
	else
	{
		keyMgrPair ret;
		ret = mapSKMgrs.insert({ k, new SingleKeyEventManager(k) });
		ret.first->second->Register(p, e);
	}
}
void KeyboardEventManager::Deregister(Inputable* p, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	auto itr = mapSKMgrs.find(k); 

	assert(itr != mapSKMgrs.end());

	(*itr).second->Deregister(p, e);

}
void KeyboardEventManager::ProcessKeyEvents()
{
	for (auto itr = mapSKMgrs.begin(); itr != mapSKMgrs.end(); ++itr)
	{
		itr->second->ProcessKeyEvent();
	}
}