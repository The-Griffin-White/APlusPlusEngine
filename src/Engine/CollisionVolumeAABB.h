#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolumeBoundingBoxBase.h"

class CollisionVolumeAABB : public CollisionVolumeBoundingBoxBase
{
public:
	/// \brief Collision volume will be a box surrounding the model in world space. It will be axis aligned and will not rotate
	/// \ingroup COLLISION
	CollisionVolumeAABB();
	virtual ~CollisionVolumeAABB() {};

	void GiveNewMinMax(const Vect& newMin, const Vect& newMax);

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