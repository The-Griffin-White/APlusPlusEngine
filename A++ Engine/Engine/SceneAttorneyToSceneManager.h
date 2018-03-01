#ifndef _SceneAttorneyToSceneManager
#define _SceneAttorneyToSceneManager

#include "Scene.h"

class SceneAttorneyToSceneManager
{
private:
	friend class SceneManager;

	static void Initialize(Scene* s) { s->Initialize(); }
	static void Update(Scene* s) { s->UpdateObjects(); s->Update(); }
	static void Draw(Scene* s) { s->DrawObjects(); s->Draw(); }

	static Camera* GetCurrentCamera(Scene* s) { return s->GetCurrentCamera(); };

};

#endif