#ifndef _MathTools
#define _MathTools

struct StandardVertex;

class MathTools
{
public:
	static void TriangleNormal(const float& p1x, const float& p1y, const float& p1z, 
							const float& p2x, const float& p2y, const float& p2z, 
							const float& p3x, const float& p3y, const float& p3z, 
							float& vx, float& vy, float& vz);
};

#endif