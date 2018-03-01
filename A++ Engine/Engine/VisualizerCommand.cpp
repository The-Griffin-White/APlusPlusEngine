#include "VisualizerCommand.h"
#include "CollisionVolumeBSphere.h"
#include "VisualizerAttorneyToCommand.h"

VisualizerCommand::VisualizerCommand(const CollisionVolumeBSphere& S, const Vect& col)
{
	color = col;
	mat = Matrix(SCALE, S.GetRadius() * Vect(1, 1, 1)) * Matrix(TRANS, S.GetCenter());
}

VisualizerCommand::~VisualizerCommand()
{
//	DebugMsg::out("Deleted VisualizerCommand\n");
}

void VisualizerCommand::execute()
{
	VisualizerAttorneyToCommand::RenderBSphere(mat, color);
}