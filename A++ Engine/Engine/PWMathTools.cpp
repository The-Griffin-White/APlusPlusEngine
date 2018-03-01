#include "PWMathTools.h"
#include "CollisionVolumeBSphere.h"

const bool PWMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
	// Get the distance between the two points with Pythagorean theorem
	// DO NOT get the square root, it's a waste
	Vect centerSum = B.GetCenter() - A.GetCenter();
	float distance = centerSum.dot(centerSum);

	// Get the sum of the two radii, then square to match the distance
	float radiusTotal = A.GetRadius() + B.GetRadius();
	radiusTotal *= radiusTotal;

	// if current distance is within radius, we collide
	return (distance <= radiusTotal);
}