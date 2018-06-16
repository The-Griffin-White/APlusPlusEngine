#ifndef _VisualizerCommandBroker
#define _VisualizerCommandBroker

#include <list>

class VisualizerCommand;

class VisualizerCommandBroker
{
public:
	VisualizerCommandBroker() {};
	~VisualizerCommandBroker();

	void AddCommand(VisualizerCommand* c);
	void ExecuteCommands();
	void Delete();

private:
	std::list<VisualizerCommand*> cmdList;

};

#endif _VisualizerCommandBroker