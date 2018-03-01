#ifndef _SceneManagerAttorneyToSceneChange
#define _SceneManagerAttorneyToSceneChange

#include "SceneManager.h"

class Scene;

class SceneManagerAttorneyToSceneChange
{
private:
	friend class SceneChangeNextCommand;
	static void SetCurrentScene(Scene* s) { SceneManager::SetCurrentScene(s); };
};

#endif