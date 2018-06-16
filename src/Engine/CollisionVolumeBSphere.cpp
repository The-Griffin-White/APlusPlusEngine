#include "CollisionVolumeBSphere.h"
#include "PWMathTools.h"
#include "Visualizer.h"
#include "VisualizerAttorneyToCollisionVolume.h"

#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
{
	Center = Vect(0, 0, 0);
	Radius = 0.0f;
}

void CollisionVolumeBSphere::ComputeData(Model* mod, Matrix& mat)
{
	// Multiply model's center and radius by world matrix
	Center = mod->getCenter() * mat;
	// Just grabbing the scale using a vector...
	Radius = mod->getRadius() * mat.get(MatrixRowType::ROW_1).Y();
}

const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return Center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return Radius;
}

void CollisionVolumeBSphere::DebugView(const Vect& col) const
{
	VisualizerAttorneyToCollisionVolume::ShowBSphere(*this, col);
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}
bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return PWMathTools::Intersect(*this, other);
}
bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return PWMathTools::Intersect(other, *this);
}
bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return PWMathTools::Intersect(other, *this);
}
bool CollisionVolumeBSphere::Intersect(const Vect& otherMin, const Vect& otherMax) const
{
	return PWMathTools::Intersect(otherMin, otherMax, *this);
}