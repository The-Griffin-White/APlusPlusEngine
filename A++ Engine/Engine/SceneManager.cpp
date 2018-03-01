#include "SceneManager.h"
#include "AzulCore.h"

#include "SceneNull.h"
#include "SceneChangeNullCommand.h"
#include "SceneChangeNextCommand.h"

SceneManager* SceneManager::ptrInstance = nullptr;

SceneManager::SceneManager()
{
	currScene = new SceneNull;
	nullCmd = new SceneChangeNullCommand;
	nextCmd = new SceneChangeNextCommand;
	currCmd = nullCmd;
}

SceneManager::~SceneManager()
{
	DebugMsg::out("Deleted SceneManager\n");
	delete currScene;
}

void SceneManager::Update()
{
	Instance().currCmd->execute();

	SceneAttorneyToSceneManager::Update(Instance().currScene);
}

void SceneManager::Draw()
{
	SceneAttorneyToSceneManager::Draw(Instance().currScene);
}

void SceneManager::privSetNextScene(Scene* ptrSc)
{
	nextCmd->SetScenePtr(ptrSc);
	currCmd = nextCmd;
}

void SceneManager::privSetCurrentScene(Scene* ptrSc)
{
	Scene* tmp = currScene;
	currScene = ptrSc;
	SceneAttorneyToSceneManager::Initialize(currScene);
	delete tmp;
	currCmd = nullCmd;
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

Camera* SceneManager::privGetCurrentCamera()
{
	return SceneAttorneyToSceneManager::GetCurrentCamera(currScene);
}