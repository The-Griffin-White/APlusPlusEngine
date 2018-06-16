#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"

class CollisionVolumeBSphere : public CollisionVolume
{
public:
	/// \brief Collision volume will be a sphere surrounding the model
	/// \ingroup COLLISION
	CollisionVolumeBSphere();

	virtual void ComputeData(Model* mod, Matrix& mat);
	virtual const Vect& GetCenter() const;
	virtual float GetRadius() const;
	virtual void DebugView(const Vect& col) const;
	// visitor pattern
	virtual bool IntersectAccept(const CollisionVolume& other) const;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const;
	virtual bool Intersect(const Vect& otherMin, const Vect& otherMax) const;

private:
	Vect Center;
	float Radius;

};

#endif