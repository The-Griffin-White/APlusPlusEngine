#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolumeBoundingBoxBase.h"

class CollisionVolumeOBB : public CollisionVolumeBoundingBoxBase
{
public:
	/// \brief Collision volume will be a box surrounding the model in model space, transformed with the models world matrix
	/// \ingroup COLLISION
	CollisionVolumeOBB(Model* const mod);
	virtual ~CollisionVolumeOBB() {};

	virtual void ComputeData(Model* mod, Matrix& mat);
	virtual void DebugView(const Vect& col) const;
	// visitor pattern
	virtual bool IntersectAccept(const CollisionVolume& other) const;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const;
	virtual bool Intersect(const Vect& otherMin, const Vect& otherMax) const;
};

#endif