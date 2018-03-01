#ifndef _CollisionVolume
#define _CollisionVolume

#include <malloc.h>
#include "AzulCore.h"
#include "Align16.h"

class CollisionVolumeBSphere;

class CollisionVolume : public Align16
{
public:
	virtual void ComputeData(Model* mod, Matrix& mat) = 0;
	virtual bool Intersect(const CollisionVolume& other) const = 0;
	virtual bool Intersect(const CollisionVolumeBSphere& other) const = 0;
};

#endif