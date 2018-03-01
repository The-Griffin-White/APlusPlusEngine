#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "SceneRegistrationCommand.h"

class GameObject;

class GameObjectEntryCommand : public SceneRegistrationCommand
{
private:
	GameObject* ptrGb;

public:
	GameObjectEntryCommand(GameObject* g);

	virtual void execute();
};

#endif