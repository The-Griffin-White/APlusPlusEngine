#include "VisualizerCommandBSphere.h"
#include "CollisionVolumeBSphere.h"
#include "VisualizerAttorneyToCommand.h"

VisualizerCommandBSphere::VisualizerCommandBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	color = col;
	mat = Matrix(SCALE, S.GetRadius() * Vect(1, 1, 1)) * Matrix(TRANS, S.GetCenter());
}

VisualizerCommandBSphere::~VisualizerCommandBSphere()
{
//	DebugMsg::out("Deleted VisualizerCommandBSphere\n");
}

void VisualizerCommandBSphere::execute()
{
	VisualizerAttorneyToCommand::RenderBSphere(mat, color);
}