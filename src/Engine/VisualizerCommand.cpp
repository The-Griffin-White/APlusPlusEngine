#include "VisualizerCommand.h"
#include "CollisionVolumeBSphere.h"
#include "VisualizerAttorneyToCommand.h"

VisualizerCommand::~VisualizerCommand()
{
//	DebugMsg::out("Deleted VisualizerCommand\n");
}

void VisualizerCommand::execute()
{
	DebugMsg::out("Executed base VisualizerCommand (BROKE)\n");
}