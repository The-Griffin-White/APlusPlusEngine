#ifndef _SceneRegistrationAttorneyToScene
#define _SceneRegistrationAttorneyToScene

#include "SceneRegistrationBroker.h"

class SceneRegistrationAttorneyToScene
{
private:
	friend class Scene;

	static void AddCommand(SceneRegistrationBroker* broker, SceneRegistrationCommand* c) 
								{ broker->AddCommand(c); };

	static void ExecuteCommands(SceneRegistrationBroker* broker) 
								{ broker->ExecuteCommands(); };

};

#endif