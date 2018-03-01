#include "Scene.h"
#include "GameObject.h"

#include "CameraManager.h"
#include "DrawableManager.h"
#include "UpdateableManager.h"
#include "AlarmableManager.h"
#include "CollisionManager.h"
#include "SceneRegistrationBroker.h"
#include "SceneRegistrationAttorneyToScene.h"
#include "Visualizer.h"

Scene::Scene()
{
	regBrkr = new SceneRegistrationBroker;
	drawMgr = new DrawableManager;
	updateMgr = new UpdateableManager;
	alarmMgr = new AlarmableManager;
	cameraMgr = new CameraManager;
	kbMgr = new KeyboardEventManager;
	colMgr = new CollisionManager;
}

Scene::~Scene()
{
	colMgr->DeleteCollidableGroups();

	delete regBrkr;
	delete drawMgr;
	delete updateMgr;
	delete alarmMgr;
	delete cameraMgr;
	delete kbMgr;
	delete colMgr;
}

void Scene::UpdateObjects()
{
	SceneRegistrationAttorneyToScene::ExecuteCommands(regBrkr);

	colMgr->ProcessCollisions();

	kbMgr->ProcessKeyEvents();

	updateMgr->ProcessElements();

	alarmMgr->ProcessElements();
}

void Scene::DrawObjects()
{
	Visualizer::Draw();

	drawMgr->ProcessElements();
}

Camera* Scene::GetCurrentCamera()
{
	return cameraMgr->Get();
}

// ***********************************************************
//      Working to replace with SceneRegistrationBroker
// ***********************************************************

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

void Scene::RegisterInputable(Inputable* in, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	kbMgr->Register(in, k, e);
}

void Scene::DeregisterInputable(Inputable* in, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	kbMgr->Deregister(in, k, e);
}

void Scene::SubmitCommand(SceneRegistrationCommand* c)
{
	SceneRegistrationAttorneyToScene::AddCommand(regBrkr, c);
}