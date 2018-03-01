#ifndef _VisualizerCommand
#define _VisualizerCommand

#include "CommandBase.h"
#include "AzulCore.h"

class CollisionVolumeBSphere;

class VisualizerCommand : public CommandBase
{
public:
	VisualizerCommand(const CollisionVolumeBSphere& S, const Vect& col);
	~VisualizerCommand();
	void execute();

private:
	VisualizerCommand();
	Matrix mat;
	Vect color;
};

#endif