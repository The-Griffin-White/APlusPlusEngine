#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "SceneRegistrationCommand.h"

class GameObject;

class GameObjectExitCommand : public SceneRegistrationCommand
{
private:
	GameObject* ptrGb;

public:
	GameObjectExitCommand(GameObject* g);

	virtual void execute();
};

#endif