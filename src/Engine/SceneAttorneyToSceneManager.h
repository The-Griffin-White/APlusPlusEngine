#ifndef _SceneAttorneyToSceneManager
#define _SceneAttorneyToSceneManager

#include "Scene.h"

class SceneAttorneyToSceneManager
{
private:
	friend class SceneManager;

	static void Initialize(Scene* s) { s->preInitialize(); s->Initialize(); }
	static void SceneEnd(Scene* s) { s->SceneEnd(); }
	static void Update(Scene* s) { s->UpdateObjects(); s->Update(); }
	static void Draw(Scene* s) { s->DrawObjects(); s->Draw(); }
	static bool GetTerrain(Scene* s, Terrain*& t) { return s->GetTerrain(t); }
	static bool GetTerrainVector(Scene* s, Collidable* col, Vect& y) { return s->GetTerrainVector(col, y); }
	static bool GetTerrainHeight(Scene* s, Collidable* col, float& y) { return s->GetTerrainHeight(col, y); }
	static bool GetTerrainPointBelowCollidable(Scene* s, Collidable* col, Vect& y) { return s->GetTerrainVector(col, y); }

	static Camera* Get2DCamera(Scene* s) { return s->Get2DCamera(); };
	static Camera* GetCurrentCamera(Scene* s) { return s->GetCurrentCamera(); };

};

#endif