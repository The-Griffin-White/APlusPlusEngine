#include "SceneRegistrationBroker.h"
#include "SceneRegistrationCommand.h"

#include "AzulCore.h"

SceneRegistrationBroker::~SceneRegistrationBroker()
{
	while (!cmdList.empty())
	{
		cmdList.pop_front();
	}
	DebugMsg::out("SceneRegistrationBroker deleted\n");
}

void SceneRegistrationBroker::AddCommand(SceneRegistrationCommand* c)
{
	cmdList.insert(cmdList.end(), c);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	SceneRegistrationCommand* c;

	while (!cmdList.empty())
	{
		c = ( *cmdList.begin() );
		c->execute();

		cmdList.pop_front();
	}
}