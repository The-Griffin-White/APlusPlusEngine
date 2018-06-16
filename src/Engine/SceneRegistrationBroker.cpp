#include "SceneRegistrationBroker.h"
#include "SceneRegistrationCommand.h"

#include "APPECore.h"

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
	auto itr = cmdList.begin();
	while (itr != cmdList.end())
	{
		(*itr)->execute(); 
		++itr;
		cmdList.pop_front();
	}
}