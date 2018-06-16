#include "SceneChangeNextCommand.h"

#include "SceneManagerAttorneyToSceneChange.h"

SceneChangeNextCommand::SceneChangeNextCommand()
	: ptrSc(nullptr)
{
}
void SceneChangeNextCommand::SetScenePtr(Scene* s)
{
	ptrSc = s;
}

SceneChangeNextCommand::~SceneChangeNextCommand()
{
	// We shouldn't delete the scene here, we're just holding it
	ptrSc = nullptr;
}

void SceneChangeNextCommand::execute()
{
	SceneManagerAttorneyToSceneChange::SetCurrentScene(ptrSc);
}