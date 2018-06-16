#ifndef _CollisionVolume
#define _CollisionVolume

#include <malloc.h>
#include "APPECore.h"
#include "Align16.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume : public Align16
{
public:
	virtual ~CollisionVolume() {};

	virtual void ComputeData(Model* mod, Matrix& mat) = 0;
	// visualizer thingy
	virtual void DebugView(const Vect& col) const = 0;
	// visitor pattern
	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;
	virtual bool Intersect(const Vect& otherMin, const Vect& otherMax) const = 0;
};

#endif