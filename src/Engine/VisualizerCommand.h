#ifndef _VisualizerCommand
#define _VisualizerCommand

#include "CommandBase.h"
#include "APPECore.h"

class VisualizerCommand : public CommandBase
{
public:
	VisualizerCommand() {};
	virtual ~VisualizerCommand();
	void execute();
};

#endif