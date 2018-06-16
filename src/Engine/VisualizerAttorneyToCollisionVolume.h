#ifndef _VisualizerAttorneyToCollisionVolume
#define _VisualizerAttorneyToCollisionVolume

#include "Visualizer.h"

class VisualizerAttorneyToCollisionVolume
{
private:
	friend class CollisionVolumeAABB;
	friend class CollisionVolumeBSphere;
	friend class CollisionVolumeOBB;

	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
	{
		Visualizer::Instance().ShowBSphere(S, col);
	};
	static void ShowAABB(const CollisionVolumeAABB& S, const Vect& col)
	{
		Visualizer::Instance().ShowAABB(S, col);
	};
	static void ShowOBB(const CollisionVolumeOBB& S, const Vect& col)
	{
		Visualizer::Instance().ShowOBB(S, col);
	};
};

#endif