#include "MathTools.h"
#include "Vect.h"
#include "Model.h"

#include <cmath>

void MathTools::TriangleNormal
(const float& p1x, const float& p1y, const float& p1z,
	const float& p2x, const float& p2y, const float& p2z,
	const float& p3x, const float& p3y, const float& p3z,
	float& vx, float& vy, float& vz)
{
	Vect A = Vect(p1x, p1y, p1z);
	Vect B = Vect(p2x, p2y, p2z);
	Vect C = Vect(p3x, p3y, p3z);

	Vect Dir = (B - A).cross(C - A);
	Vect Norm = Dir.getNorm();

	vx = Norm.X();
	vy = Norm.Y();
	vz = Norm.Z();

	/*
	Vect U;
	U.set(p2x - p1x, p2y - p1y, p2z - p1z);
	Vect V;
	V.set(p3x - p2x, p3y - p2y, p3z - p2z);

	vx = (U.Y() * V.Z()) - (U.Z() * V.Y());
	vy = (U.Z() * V.X()) - (U.X() * V.Z());
	vz = (U.X() * V.Y()) - (U.Y() * V.X());
	//*/
}