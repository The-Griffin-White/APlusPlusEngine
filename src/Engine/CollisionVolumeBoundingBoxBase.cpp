#include "CollisionVolumeBoundingBoxBase.h"

CollisionVolumeBoundingBoxBase::~CollisionVolumeBoundingBoxBase()
{
	DebugMsg::out("Deleted CollisionVolumeBoundingBoxBase\n");
}

const Vect& CollisionVolumeBoundingBoxBase::GetMax() const
{
	return max;
}
const Vect& CollisionVolumeBoundingBoxBase::GetMin() const
{
	return min;
}
const Vect& CollisionVolumeBoundingBoxBase::GetHalfDiagonal() const
{
	return halfDiag;
}
const Vect& CollisionVolumeBoundingBoxBase::GetWorldCenter() const
{
	return worldCenter;
}
const float& CollisionVolumeBoundingBoxBase::GetScaleFactor() const
{
	return scaleFactor;
}
const Matrix& CollisionVolumeBoundingBoxBase::GetWorld() const
{
	return world;
}