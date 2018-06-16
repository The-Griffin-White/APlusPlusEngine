#ifndef _VisualizerCommandBSphere
#define _VisualizerCommandBSphere

#include "VisualizerCommand.h"
#include "APPECore.h"

class CollisionVolumeBSphere;

class VisualizerCommandBSphere : public VisualizerCommand
{
public:
	VisualizerCommandBSphere(const CollisionVolumeBSphere& S, const Vect& col);
	virtual ~VisualizerCommandBSphere();
	void execute();

private:
	VisualizerCommandBSphere();
	Matrix mat;
	Vect color;
};

#endif