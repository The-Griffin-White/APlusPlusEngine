#include "GameObject.h"
#include "SceneManager.h"

#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"

#include "SceneAttorneyToGameObject.h"

GameObject::GameObject()
{
	registeredToScene = false;

	pRegistrationCmd = new GameObjectEntryCommand(this);
	pDeregistrationCmd = new GameObjectExitCommand(this);
}

GameObject::~GameObject()
{
	DebugMsg::out("Deleted GameObject\n");
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

void GameObject::ConnectToScene()
{
	if (!registeredToScene)
	{
		this->SceneEntry();
		registeredToScene = true;
	}
}

void GameObject::DisconnectToScene()
{
	if (registeredToScene)
	{
		this->SceneExit();
		registeredToScene = false;
	}
}

void GameObject::SubmitEntry()
{
	SceneAttorneyToGameObject::SubmitCommand(pRegistrationCmd);
}
void GameObject::SubmitExit()
{
	SceneAttorneyToGameObject::SubmitCommand(pDeregistrationCmd);
}