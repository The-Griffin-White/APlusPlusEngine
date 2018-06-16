#ifndef _VisualizerCommandAABB
#define _VisualizerCommandAABB

#include "VisualizerCommand.h"
#include "APPECore.h"

class CollisionVolumeAABB;

class VisualizerCommandAABB : public VisualizerCommand
{
public:
	VisualizerCommandAABB(const CollisionVolumeAABB& S, const Vect& col);
	VisualizerCommandAABB(const Vect& min, const Vect& max, const Vect& col);
	virtual ~VisualizerCommandAABB();
	void execute();

private:
	VisualizerCommandAABB();
	Matrix mat;
	Vect center;
	Vect color;
};

#endif