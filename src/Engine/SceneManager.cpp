#include "SceneManager.h"
#include "APPECore.h"

#include "Scene.h"
#include "SceneNull.h"
#include "SceneChangeNullCommand.h"
#include "SceneChangeNextCommand.h"

SceneManager* SceneManager::ptrInstance = nullptr;

SceneManager::SceneManager()
{
	currScene = new SceneNull;
	nullCmd = new SceneChangeNullCommand;
	swapCmd = nullCmd;
	nextCmd = new SceneChangeNextCommand;
	currCmd = nullCmd;
}

SceneManager::~SceneManager()
{
//	DebugMsg::out("Deleted SceneManager\n");
	delete currScene;
	delete nullCmd;
	delete nextCmd;
}

void SceneManager::Update()
{
	SceneAttorneyToSceneManager::Update(Instance().currScene);

	Instance().currCmd->execute();
	Instance().LoadNextScene();
}

void SceneManager::Draw()
{
	SceneAttorneyToSceneManager::Draw(Instance().currScene);
}

void SceneManager::privSetNextScene(Scene* ptrSc)
{
	SceneAttorneyToSceneManager::SceneEnd(currScene);
	nextCmd->SetScenePtr(ptrSc);
	swapCmd = nextCmd;
}

void SceneManager::LoadNextScene()
{
	currCmd = swapCmd;
}

void SceneManager::privSetCurrentScene(Scene* ptrSc)
{
	Scene* tmp = currScene;
	currScene = ptrSc;
	delete tmp;
	SceneAttorneyToSceneManager::Initialize(currScene);
	swapCmd = nullCmd;
}

void SceneManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

Scene* SceneManager::privGet()
{
	return currScene;
}

Camera* SceneManager::privGet2DCamera()
{
	return SceneAttorneyToSceneManager::Get2DCamera(currScene);
}

Camera* SceneManager::privGetCurrentCamera()
{
	return SceneAttorneyToSceneManager::GetCurrentCamera(currScene);
}

bool SceneManager::GetTerrain(Terrain*& t)
{
	return SceneAttorneyToSceneManager::GetTerrain(Instance().currScene, t);
}

bool SceneManager::GetTerrainVector(Collidable* col, Vect& up)
{
	return SceneAttorneyToSceneManager::GetTerrainVector(Instance().currScene, col, up);
}

bool SceneManager::GetTerrainHeight(Collidable* col, float& y)
{
	return SceneAttorneyToSceneManager::GetTerrainHeight(Instance().currScene, col, y);
}

bool SceneManager::GetTerrainPointBelowCollidable(Collidable* col, Vect& p)
{
	return SceneAttorneyToSceneManager::GetTerrainPointBelowCollidable(Instance().currScene, col, p);
}