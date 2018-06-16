#include "SceneAttorneyToInputable.h"

#include "Scene.h"
#include "SceneManager.h"

void SceneAttorneyToInputable::SubmitCommand(SceneRegistrationCommand* c)
{
	SceneManager::Get()->SubmitCommand(c);
};

SceneAttorneyToInputable::KeyMgrRef SceneAttorneyToInputable::Register(Inputable* in, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	return SceneManager::Get()->RegisterInputable(in, k, e);
};

void SceneAttorneyToInputable::Deregister(Inputable::KeyMgrRef keyRef, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e)
{
	SceneManager::Get()->DeregisterInputable(keyRef, k, e);
};