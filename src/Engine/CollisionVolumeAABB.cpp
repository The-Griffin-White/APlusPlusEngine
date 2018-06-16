#include "CollisionVolumeAABB.h"
#include "PWMathTools.h"
#include "Visualizer.h"
#include "VisualizerAttorneyToCollisionVolume.h"
#include <limits>

#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeOBB.h"

CollisionVolumeAABB::CollisionVolumeAABB()
{
}

void CollisionVolumeAABB::GiveNewMinMax(const Vect& newMin, const Vect& newMax)
{
	min = newMin;
	max = newMax;

	world = Matrix(IDENTITY);

	halfDiag = (max - min) * 0.5f;
	worldCenter = min + halfDiag;
	// squaring it for optimized math functions (see PWMathTools.cpp for implementation)
	// we're assuming uniform scaling
	scaleFactor = 1;
}

void CollisionVolumeAABB::ComputeData(Model* mod, Matrix& mat)
{
	float inf = std::numeric_limits<float>::infinity();

	min = Vect(inf, inf, inf);
	max = Vect(-inf, -inf, -inf);

	const int num = mod->getVectNum();
	const Vect* list = new Vect[num];
	list = mod->getVectList();

	Vect tmp;

	for (int i = 0; i < num; ++i)
	{
		tmp = list[i] * mat;
		// if statements galore, i guess...
			// check if above max
		if (tmp.X() > max.X())
		{
			max.X() = tmp.X();
		}
		if (tmp.Y() > max.Y())
		{
			max.Y() = tmp.Y();
		}
		if (tmp.Z() > max.Z())
		{
			max.Z() = tmp.Z();
		}
		// if statements galore, i guess...
			// check if below min
		if (tmp.X() < min.X())
		{
			min.X() = tmp.X();
		}
		if (tmp.Y() < min.Y())
		{
			min.Y() = tmp.Y();
		}
		if (tmp.Z() < min.Z())
		{
			min.Z() = tmp.Z();
		}
	}

	world = Matrix(IDENTITY);

	halfDiag = (max - min) * 0.5f;
	worldCenter = min + halfDiag;
	// squaring it for optimized math functions (see PWMathTools.cpp for implementation)
	// we're assuming uniform scaling
	scaleFactor = 1;
}
void CollisionVolumeAABB::DebugView(const Vect& col) const
{
	VisualizerAttorneyToCollisionVolume::ShowAABB(*this, col);
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}
bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return PWMathTools::Intersect(*this, other);
}
bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return PWMathTools::Intersect(*this, other);
}
bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return PWMathTools::Intersect(other, *this);
}
bool CollisionVolumeAABB::Intersect(const Vect& otherMin, const Vect& otherMax) const
{
	return PWMathTools::Intersect(otherMin, otherMax, *this);
}