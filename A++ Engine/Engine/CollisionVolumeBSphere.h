#ifndef _CollisionVolumeBSphere
#define _CollisonVolumeBSphere

#include "CollisionVolume.h"

class CollisionVolumeBSphere : public CollisionVolume
{
public:
	CollisionVolumeBSphere();

	virtual void ComputeData(Model* mod, Matrix& mat);
	virtual const Vect& GetCenter() const;
	virtual float GetRadius() const;
	virtual bool Intersect(const CollisionVolume& other) const override { other; return true; };
	virtual bool Intersect(const CollisionVolumeBSphere& other) const override;

private:
	Vect Center;
	float Radius;

};

#endif