#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <list>

class SceneRegistrationCommand;

class SceneRegistrationBroker
{
public:
	SceneRegistrationBroker() {};
	~SceneRegistrationBroker();

private:
	std::list<SceneRegistrationCommand*> cmdList;

	friend class SceneRegistrationAttorneyToScene;

	/// \brief Add a command of any type SceneRegistrationCommand to the Broker for processing next frame.
	/// \ingroup SCENE-REGISTER
	void AddCommand(SceneRegistrationCommand* c);
	/// \brief Executes all of the commands that were added last frame.
	/// \ingroup SCENE-REGISTER
	void ExecuteCommands();

};

#endif