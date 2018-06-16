#ifndef _PWMathTools
#define _PWMathTools

class Collidable;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeBoundingBoxBase;
class Vect;

class PWMathTools
{
public:
	/// \brief Math to get the barycentric coordinate between 3 points
	/// \ingroup UTIL
	// Used for movement along terrain
	static Vect BarycentricCoordinate(const Vect P, const Vect A, const Vect B, const Vect C, float& beta, float& gamma);

	/// \brief Math to determine the normal of a plane based on three points
	/// \ingroup UTIL
	// Used for terrain generation
	static void TriangleNormal(const float& p1x, const float& p1y, const float& p1z,
		const float& p2x, const float& p2y, const float& p2z,
		const float& p3x, const float& p3y, const float& p3z,
		float& vx, float& vy, float& vz);

	// Collision Stuff
	static const bool Intersect(const Collidable* A, const Collidable* B);
	static const bool Intersect(const Collidable* A, const CollisionVolumeAABB& B);
	static const bool Intersect(const Collidable* A, const CollisionVolumeBSphere& B);
	static const bool IntersectBSpheres(const Collidable* A, const Collidable* B);
	static const bool Intersect(const Vect& min, const Vect& max, const Collidable* B);

	/// \brief Math for intersection between two bounding spheres
	/// \ingroup UTIL
	static const bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);

	/// \brief Math for intersection between two axis-aligned bounding boxes
	/// \ingroup UTIL
	static const bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B);
	static const bool Intersect(const Vect& min, const Vect& max, const CollisionVolumeAABB& B);
	/// \brief Math for intersection between an AABB and BSphere
	/// \ingroup UTIL
	static const bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeBSphere& B);
	static const bool Intersect(const Vect& min, const Vect& max, const CollisionVolumeBSphere& B);

	/// \brief Math for intersection between Two Oriented Bounding Boxes
	/// \ingroup UTIL
	static const bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);
	/// \brief Math for intersection between an AABB and OBB
	/// \ingroup UTIL
	static const bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B);
	static const bool Intersect(const Vect& min, const Vect& max, const CollisionVolumeOBB& A);
	/// \brief Math for intersection between an OBB and BSphere
	/// \ingroup UTIL
	static const bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeBSphere& B);

	static const bool IntervalTest(const float& a, const float& b, const float& c, const float& d);
	static const Vect Clamp(const Vect& c, const Vect& max, const Vect& min);

	static const float MaxProjection(const Vect& v, const CollisionVolumeBoundingBoxBase& A);
	static const float MaxProjection(const Vect& v, const Vect& min, const Vect& max);
	static const bool AxisOverlapTest(const Vect v[15], const CollisionVolumeBoundingBoxBase& A, const CollisionVolumeBoundingBoxBase& B);
	static const bool AxisOverlapTest(const Vect v[15], const CollisionVolumeBoundingBoxBase& A, const Vect& min, const Vect& max);
};

#endif