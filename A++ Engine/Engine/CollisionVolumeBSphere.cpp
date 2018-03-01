#include "CollisionVolumeBSphere.h"
#include "PWMathTools.h"

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

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeBSphere& other) const
{
	// Annoying that we dereference here, but really it's fine...
	return PWMathTools::Intersect(*this, other);
}
