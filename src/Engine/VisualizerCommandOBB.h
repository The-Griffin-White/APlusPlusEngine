#ifndef _VisualizerCommandOBB
#define _VisualizerCommandOBB

#include "VisualizerCommand.h"
#include "APPECore.h"

class CollisionVolumeOBB;

class VisualizerCommandOBB : public VisualizerCommand
{
public:
	VisualizerCommandOBB(const CollisionVolumeOBB& S, const Vect& col);
	virtual ~VisualizerCommandOBB();
	void execute();

private:
	VisualizerCommandOBB();
	Matrix mat;
	Vect center;
	Vect color;
};

#endif