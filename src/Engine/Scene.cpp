#include "Scene.h"
#include "GameObject.h"

#include "CameraManager.h"
#include "DrawableManager.h"
#include "UpdateableManager.h"
#include "AlarmableManager.h"
#include "CollisionManager.h"
#include "SceneRegistrationBroker.h"
#include "SceneRegistrationAttorneyToScene.h"
#include "SpriteManagerAttorneyToScene.h"
#include "Visualizer.h"

#include "Terrain.h"
#include "TerrainManager.h"

Scene::Scene()
{
	SFXManager::ChangeDirectionalLighting(Vect(0, -.25f, 0).getNorm(),
		0.5f * Vect(1, 1, 1), 1 * Vect(1, 1, 1), 0.1f * Vect(1, 1, 1));
	SFXManager::SetDisableFog();

	cameraMgr = new CameraManager;
	regBrkr = new SceneRegistrationBroker;
	drawMgr = new DrawableManager;
	updateMgr = new UpdateableManager;
	alarmMgr = new AlarmableManager;
	cameraMgr = new CameraManager;
	kbMgr = new KeyboardEventManager;
	sprMgr = new SpriteManager;
	colMgr = nullptr;
}

Scene::~Scene()
{
	delete regBrkr;
	delete drawMgr;
	delete updateMgr;
	delete alarmMgr;
	delete cameraMgr;
	delete kbMgr;
	delete sprMgr;
	if (colMgr) delete colMgr;
}

void Scene::preInitialize()
{
	colMgr = new CollisionManager;
}

void Scene::UpdateObjects()
{
	SceneRegistrationAttorneyToScene::ExecuteCommands(regBrkr);

	kbMgr->ProcessKeyEvents();

	alarmMgr->ProcessElements();

	updateMgr->ProcessElements();

	SpriteManagerAttorneyToScene::Update(sprMgr);

	colMgr->ProcessCollisions();
}

void Scene::DrawObjects()
{
	SkyBoxManager::Draw();

	drawMgr->ProcessElements();

	Visualizer::Draw();

	SpriteManagerAttorneyToScene::Draw(sprMgr);
}

Camera* Scene::Get2DCamera()
{
	return cameraMgr->Get2D();
}

Camera* Scene::GetCurrentCamera()
{
	return cameraMgr->Get();
}

void Scene::SetTerrain(std::string terrName)
{
	currTerrain = TerrainManager::Get(terrName);
	currTerrain->SubmitEntry();
}

SpriteManager::SpriteListRef Scene::AddSprite(Sprite* s)
{
	return sprMgr->AddSprite(s);
}
void Scene::RemoveSprite(SpriteManager::SpriteListRef p)
{
	sprMgr->RemoveSprite(p);
}

UpdateableManager::UpdateableListRef Scene::RegisterUpdateable(Updateable* up)
{
	return updateMgr->Register(up);
}
void Scene::DeregisterUpdateable(UpdateableManager::UpdateableListRef itr)
{
	updateMgr->Deregister(itr);
}
DrawableManager::DrawableListRef Scene::RegisterDrawable(Drawable* dr)
{
	return drawMgr->Register(dr);
}
void Scene::DeregisterDrawable(DrawableManager::DrawableListRef itr)
{
	drawMgr->Deregister(itr);
}
AlarmableManager::TimelineRef Scene::RegisterAlarmable(Alarmable* al, AlarmableManager::ALARM_ID id, float t)
{
	return alarmMgr->Register(al, id, t);
}

void Scene::DeregisterAlarmable(AlarmableManager::TimelineRef itr)
{
	alarmMgr->Deregister(itr);
}

KeyboardEventManager::KeyMgrRef Scene::RegisterInputable(Inputable* in, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	return kbMgr->Register(in, k, e);
}

void Scene::DeregisterInputable(Inputable::KeyMgrRef keyRef, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	kbMgr->Deregister(keyRef, k, e);
}

void Scene::SubmitCommand(SceneRegistrationCommand* c)
{
	SceneRegistrationAttorneyToScene::AddCommand(regBrkr, c);
}

bool Scene::GetTerrain(Terrain*& t)
{
	t = currTerrain;
	// If nullptr, should return as false...
	return t;
}

bool Scene::GetTerrainVector(Collidable* col, Vect& up)
{
	if (currTerrain)
		return currTerrain->GetNormal(col, up);
	else
		return false;
}

bool Scene::GetTerrainHeight(Collidable* col, float& y)
{
	if (currTerrain)
		return currTerrain->GetHeight(col, y);
	else
		return false;
}

bool Scene::GetTerrainPointBelowCollidable(Collidable* col, Vect& p)
{
	if (currTerrain)
		return currTerrain->PointUnderCollidable(col, p);
	else
		return false;
}

void Scene::SetTerrainMaterial(const Vect ambient, const Vect diffuse, const Vect specular)
{
	if (currTerrain)
		currTerrain->SetMaterial(ambient, diffuse, specular);
}