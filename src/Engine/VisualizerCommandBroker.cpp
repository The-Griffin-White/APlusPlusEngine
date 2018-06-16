#include "VisualizerCommandBroker.h"
#include "VisualizerCommand.h"

#include "APPECore.h"

VisualizerCommandBroker::~VisualizerCommandBroker()
{
	this->Delete();
	DebugMsg::out("VisualizerCommandBroker deleted\n");
}

void VisualizerCommandBroker::Delete()
{
	while (!cmdList.empty())
	{
		VisualizerCommand* tmp = cmdList.front();
		cmdList.front() = nullptr;
		delete tmp;
		cmdList.pop_front();
	}
}

void VisualizerCommandBroker::AddCommand(VisualizerCommand* c)
{
	cmdList.insert(cmdList.end(), c);
}

void VisualizerCommandBroker::ExecuteCommands()
{
	VisualizerCommand* c;

	while (!cmdList.empty())
	{
		c = (*cmdList.begin());
		c->execute();

		VisualizerCommand* tmp = cmdList.front();
		cmdList.front() = nullptr;
		delete tmp;
		cmdList.pop_front();
	}
}