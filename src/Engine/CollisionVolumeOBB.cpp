#include "CollisionVolumeOBB.h"
#include "PWMathTools.h"
#include "Visualizer.h"
#include "VisualizerAttorneyToCollisionVolume.h"
#include <limits>

#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"

CollisionVolumeOBB::CollisionVolumeOBB(Model* const mod)
{
	min = mod->getMinAABB();
	max = mod->getMaxAABB();

	halfDiag = (max - min) * 0.5f;
}

void CollisionVolumeOBB::ComputeData(Model* mod, Matrix& mat)
{
	mod;		// obb doesnt need anything from here to update
	world = mat;
	worldCenter = (min + halfDiag) * world;
	// squaring it for optimized math functions (see PWMathTools.cpp for implementation)
	// we're assuming uniform scaling
	scaleFactor = world.get(MatrixRowType::ROW_1).Y() * world.get(MatrixRowType::ROW_1).Y();
}

void CollisionVolumeOBB::DebugView(const Vect& col) const
{
	VisualizerAttorneyToCollisionVolume::ShowOBB(*this, col);
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}
bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return PWMathTools::Intersect(*this, other);
}
bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return PWMathTools::Intersect(*this, other);
}
bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return PWMathTools::Intersect(*this, other);
}
bool CollisionVolumeOBB::Intersect(const Vect& otherMin, const Vect& otherMax) const
{
	return PWMathTools::Intersect(otherMin, otherMax, *this);
}