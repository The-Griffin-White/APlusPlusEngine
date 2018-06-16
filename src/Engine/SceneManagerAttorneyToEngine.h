#ifndef _SceneManagerAttorneyToEngine
#define _SceneManagerAttorneyToEngine

#include "SceneManager.h"

class SceneManagerAttorneyToEngine
{
private:
	friend class APlusPlusEngine;
	static void Terminate() { SceneManager::Terminate(); };
};

#endif