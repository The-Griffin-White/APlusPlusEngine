#include "PWMathTools.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "Collidable.h"


Vect PWMathTools::BarycentricCoordinate(const Vect P, const Vect A, const Vect B, const Vect C, float& beta, float& gamma)
{
	Vect p2, a2, b2, c2;
	p2 = Vect(P.X(), 0, P.Z());
	a2 = Vect(A.X(), 0, A.Z());
	b2 = Vect(B.X(), 0, B.Z());
	c2 = Vect(C.X(), 0, C.Z());

	Vect v0, v1, v2;
	v0 = b2 - a2;
	v1 = c2 - b2;
	v2 = p2 - a2;

	//*
	float a, b, c, d, e;
	a = v0.dot(v0);
	b = v1.dot(v0);
	c = v1.dot(v1);
	d = v2.dot(v0);
	e = v2.dot(v1);

	beta = (d * c - b * e) / (a * c - b * b);
	gamma = (a * e - d * b) / (a * c - b * b);

	// Return Q without setting to local variable
	//*/

	return (A + (beta * (B - A)) + (gamma * (C - B)));
}

void PWMathTools::TriangleNormal
(const float& p1x, const float& p1y, const float& p1z,
	const float& p2x, const float& p2y, const float& p2z,
	const float& p3x, const float& p3y, const float& p3z,
	float& vx, float& vy, float& vz)
{
	Vect U(p2x - p1x, p2y - p1y, p2z - p1z);
	Vect V(p3x - p1x, p3y - p1y, p3z - p1z);

	Vect ret = U.cross(V);
	ret.norm();

	vx = ret.X();
	vy = ret.Y();
	vz = ret.Z();
}

const bool PWMathTools::Intersect(const Collidable* A, const Collidable* B)
{
	const CollisionVolume& v1 = A->GetCollisionVolume();
	const CollisionVolume& v2 = B->GetCollisionVolume();

	return v1.IntersectAccept(v2);
}

const bool PWMathTools::IntersectBSpheres(const Collidable* A, const Collidable* B)
{
	const CollisionVolume& v1 = *A->GetCollisionBSphere();
	const CollisionVolume& v2 = *B->GetCollisionBSphere();

	return v1.IntersectAccept(v2);
}

const bool PWMathTools::Intersect(const Collidable* A, const CollisionVolumeAABB& B)
{
	const CollisionVolume& v1 = *A->GetCollisionBSphere();

	return v1.IntersectAccept(B);
}

const bool PWMathTools::Intersect(const Collidable* A, const CollisionVolumeBSphere& B)
{
	const CollisionVolume& v1 = A->GetCollisionVolume();

	return v1.IntersectAccept(B);
}

const bool PWMathTools::Intersect(const Vect& min, const Vect& max, const Collidable* B)
{
	const CollisionVolume& v1 = B->GetCollisionVolume();

	return v1.Intersect(min, max);
}

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

const bool PWMathTools::IntervalTest(const float& a, const float& b, const float& c, const float& d)
{
	return (b >= c && d >= a);
}

const Vect PWMathTools::Clamp(const Vect& c, const Vect& max, const Vect& min)
{
	Vect ret = c;

	if (ret.X() > max.X())
	{
		ret.X() = max.X();
	}
	else if (ret.X() < min.X())
	{
		ret.X() = min.X();
	}

	if (ret.Y() > max.Y())
	{
		ret.Y() = max.Y();
	}
	else if (ret.Y() < min.Y())
	{
		ret.Y() = min.Y();
	}

	if (ret.Z() > max.Z())
	{
		ret.Z() = max.Z();
	}
	else if (ret.Z() < min.Z())
	{
		ret.Z() = min.Z();
	}

	return ret;
}

const float PWMathTools::MaxProjection(const Vect& v, const Vect& min, const Vect& max)
{
	Vect vlocal = v;
	Vect m = (max - min) * 0.5f;

	float projMax = (fabsf(vlocal.X() * m.X()) + fabsf(vlocal.Y() * m.Y()) + fabsf(vlocal.Z() * m.Z())) / v.mag();

	return projMax;
}

const float PWMathTools::MaxProjection(const Vect& v, const CollisionVolumeBoundingBoxBase& A)
{
	Vect vlocal = v * A.GetWorld().getInv();
	Vect m = A.GetHalfDiagonal();

	float projMax = (fabsf(vlocal.X() * m.X()) + fabsf(vlocal.Y() * m.Y()) + fabsf(vlocal.Z() * m.Z())) / v.mag();

	return A.GetScaleFactor() * projMax;
}

const bool PWMathTools::AxisOverlapTest(const Vect v[15], const CollisionVolumeBoundingBoxBase& A, const Vect& min, const Vect& max)
{
	float D;
	
	Vect bWorldCenter = min + ( (max - min) * 0.5f );

	for (int i = 0; i < 15; ++i)
	{
		float proj1 = PWMathTools::MaxProjection(v[i], A);
		float proj2 = PWMathTools::MaxProjection(v[i], min, max);
		D = abs((A.GetWorldCenter() - bWorldCenter).dot(v[i])) / v[i].mag();
		if (D > proj1 + proj2)
			return false;
	}

	return true;
}
const bool PWMathTools::AxisOverlapTest(const Vect v[15], const CollisionVolumeBoundingBoxBase& A, const CollisionVolumeBoundingBoxBase& B)
{
	float D;

	for (int i = 0; i < 15; ++i)
	{
		float proj1 = PWMathTools::MaxProjection(v[i], A);
		float proj2 = PWMathTools::MaxProjection(v[i], B);
		D = abs((A.GetWorldCenter() - B.GetWorldCenter()).dot(v[i])) / v[i].mag();
		if (D > proj1 + proj2)
			return false;
	}

	return true;
}

const bool PWMathTools::Intersect(const Vect& min, const Vect& max, const CollisionVolumeAABB& B)
{
	// For all 3 axes, test if A's axis intervals overlap with B's intervals
	// if true for all three axes: they intersect

	/*
	So A is { x[0, 3], y[-1, 2], z[-4, 4] } B is { x[1, 2], y[-3, -2], z[0, 8] }
	x intersects
	y does not intersect
	z intersects
	*/

	// Test X limits
	if (!PWMathTools::IntervalTest(min.X(), max.X(), B.GetMin().X(), B.GetMax().X()))
		return false;

	// Test Y limits
	if (!PWMathTools::IntervalTest(min.Y(), max.Y(), B.GetMin().Y(), B.GetMax().Y()))
		return false;

	// Test Z limits
	if (!PWMathTools::IntervalTest(min.Z(), max.Z(), B.GetMin().Z(), B.GetMax().Z()))
		return false;

	return true;
}

const bool PWMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B)
{
	// For all 3 axes, test if A's axis intervals overlap with B's intervals
		// if true for all three axes: they intersect

	/*
		So A is { x[0, 3], y[-1, 2], z[-4, 4] } B is { x[1, 2], y[-3, -2], z[0, 8] }
		x intersects
		y does not intersect
		z intersects
	*/

	// Test X limits
	if ( !PWMathTools::IntervalTest(A.GetMin().X(), A.GetMax().X(), B.GetMin().X(), B.GetMax().X()) )
		return false;

	// Test Y limits
	if ( !PWMathTools::IntervalTest(A.GetMin().Y(), A.GetMax().Y(), B.GetMin().Y(), B.GetMax().Y()) )
		return false;

	// Test Z limits
	if ( !PWMathTools::IntervalTest(A.GetMin().Z(), A.GetMax().Z(), B.GetMin().Z(), B.GetMax().Z()) )
		return false;

	return true;
}

const bool PWMathTools::Intersect(const Vect& min, const Vect& max, const CollisionVolumeBSphere& B)
{
	// Clamp the CENTER of the BSphere to the AABB (all three axes)
	// Test if the CLAMPED POINT intersects with the original sphere
	/*
	Clamping c to interval [a, b]
	if c < a return a
	else if c > b return b
	else return c
	*/
	Vect clamp = PWMathTools::Clamp(B.GetCenter(), max, min);

	// Get the distance between the two points with Pythagorean theorem
	// DO NOT get the square root, it's a waste
	Vect centerSum = B.GetCenter() - clamp;
	float distance = centerSum.dot(centerSum);

	// Square the radius to match distance
	float radiusTotal = B.GetRadius() * B.GetRadius();

	// if current distance is within radius, we collide
	return (distance <= radiusTotal);
}

const bool PWMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeBSphere& B)
{
	// Clamp the CENTER of the BSphere to the AABB (all three axes)
		// Test if the CLAMPED POINT intersects with the original sphere
	/*
		Clamping c to interval [a, b]
		if c < a return a
		else if c > b return b
		else return c
	*/
	Vect clamp = PWMathTools::Clamp(B.GetCenter(), A.GetMax(), A.GetMin());

	// Get the distance between the two points with Pythagorean theorem
	// DO NOT get the square root, it's a waste
	Vect centerSum = B.GetCenter() - clamp;
	float distance = centerSum.dot(centerSum);

	// Square the radius to match distance
	float radiusTotal = B.GetRadius() * B.GetRadius();

	// if current distance is within radius, we collide
	return (distance <= radiusTotal);
}

const bool PWMathTools::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B)
{
	// We need 15 vectors total, so...
	Vect vectors[15];

	// Get the vectors
	vectors[0] = A.GetWorld().get(MatrixRowType::ROW_0);
	vectors[1] = A.GetWorld().get(MatrixRowType::ROW_1);
	vectors[2] = A.GetWorld().get(MatrixRowType::ROW_2);
	vectors[3] = B.GetWorld().get(MatrixRowType::ROW_0);
	vectors[4] = B.GetWorld().get(MatrixRowType::ROW_1);
	vectors[5] = B.GetWorld().get(MatrixRowType::ROW_2);

	// get the cross-products of each
	int num1 = 0;
	int num2 = 3;

	for (int i = 6; i < 15; ++i)
	{
		vectors[i] = vectors[num1].cross(vectors[num2]);
		++num2;
		if (num2 > 5)
		{
			num2 = 3;
			++num1;
		}
	}

	return PWMathTools::AxisOverlapTest(vectors, A, B);
}

const bool PWMathTools::Intersect(const Vect& min, const Vect& max, const CollisionVolumeOBB& A)
{
	// We need 15 vectors total, so...
	Vect vectors[15];

	Matrix bWorld = Matrix(IDENTITY);

	// Get the vectors
	vectors[0] = A.GetWorld().get(MatrixRowType::ROW_0);
	vectors[1] = A.GetWorld().get(MatrixRowType::ROW_1);
	vectors[2] = A.GetWorld().get(MatrixRowType::ROW_2);
	vectors[3] = bWorld.get(MatrixRowType::ROW_0);
	vectors[4] = bWorld.get(MatrixRowType::ROW_1);
	vectors[5] = bWorld.get(MatrixRowType::ROW_2);

	// get the cross-products of each
	int num1 = 0;
	int num2 = 3;

	for (int i = 6; i < 15; ++i)
	{
		vectors[i] = vectors[num1].cross(vectors[num2]);
		++num2;
		if (num2 > 5)
		{
			num2 = 3;
			++num1;
		}
	}

	return PWMathTools::AxisOverlapTest(vectors, A, min, max);
}

const bool PWMathTools::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B)
{
	// We need 15 vectors total, so...
	Vect vectors[15];

	// Get the vectors
	vectors[0] = A.GetWorld().get(MatrixRowType::ROW_0);
	vectors[1] = A.GetWorld().get(MatrixRowType::ROW_1);
	vectors[2] = A.GetWorld().get(MatrixRowType::ROW_2);
	vectors[3] = B.GetWorld().get(MatrixRowType::ROW_0);
	vectors[4] = B.GetWorld().get(MatrixRowType::ROW_1);
	vectors[5] = B.GetWorld().get(MatrixRowType::ROW_2);

	// get the cross-products of each
	int num1 = 0;
	int num2 = 3;

	for (int i = 6; i < 15; ++i)
	{
		vectors[i] = vectors[num1].cross(vectors[num2]);
		++num2;
		if (num2 > 5)
		{
			num2 = 3;
			++num1;
		}
	}

	return PWMathTools::AxisOverlapTest(vectors, A, B);
}

const bool PWMathTools::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeBSphere& B)
{
	// Get the BSphere into local space (inverse OBB world space)
	Vect clamp = B.GetCenter() * A.GetWorld().getInv();

	// Clamp the CENTER of the BSphere to the OBB (all three axes)
	// Test if the CLAMPED POINT intersects with the original sphere
	/*
	Clamping c to interval [a, b]
	if c < a return a
	else if c > b return b
	else return c
	*/
	clamp = PWMathTools::Clamp(clamp, A.GetMax(), A.GetMin());

	// Move the clamped point back to world space
	clamp = clamp * A.GetWorld();

	// Get the distance between the two points with Pythagorean theorem
	// DO NOT get the square root, it's a waste
	Vect centerSum = B.GetCenter() - clamp;
	float distance = centerSum.dot(centerSum);

	// Square the radius to match distance
	float radiusTotal = B.GetRadius() * B.GetRadius();

	// if current distance is within radius, we collide
	return (distance <= radiusTotal);
}