#ifndef _CollisionVolumeBoundingBoxBase
#define _CollisionVolumeBoundingBoxBase

#include "CollisionVolume.h"

class CollisionVolumeBoundingBoxBase : public CollisionVolume
{
public:
	CollisionVolumeBoundingBoxBase() {};
	virtual ~CollisionVolumeBoundingBoxBase();

	const Vect& GetMax() const;
	const Vect& GetMin() const;
	const Vect& GetHalfDiagonal() const;
	const Vect& GetWorldCenter() const;
	const float& GetScaleFactor() const;
	const Matrix& GetWorld() const;

	virtual void ComputeData(Model* mod, Matrix& mat) { mod; mat; };
	virtual void DebugView(const Vect& col) const { col; };
	// visitor pattern, shouldn't do anything here
	virtual bool IntersectAccept(const CollisionVolume&) const { return false; };
	virtual bool IntersectVisit(const CollisionVolumeBSphere&) const { return false; };
	virtual bool IntersectVisit(const CollisionVolumeAABB&) const { return false; };
	virtual bool IntersectVisit(const CollisionVolumeOBB&) const { return false; };
	virtual bool Intersect(const Vect&, const Vect&) const { return false; };

protected:
	Vect min;
	Vect max;
	Vect halfDiag;
	Vect worldCenter;
	float scaleFactor;
	Matrix world;		// needs to be updated for visualizer
};

#endif