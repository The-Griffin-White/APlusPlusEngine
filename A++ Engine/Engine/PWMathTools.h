#ifndef _PWMathTools
#define _PWMathTools

class CollisionVolumeBSphere;

class PWMathTools
{
public:
	/// \brief Math for intersection between two bounding spheres
	/// \ingroup UTIL
	static const bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);
};

#endif