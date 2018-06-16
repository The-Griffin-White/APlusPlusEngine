#include "VisualizerCommandOBB.h"
#include "CollisionVolumeOBB.h"
#include "VisualizerAttorneyToCommand.h"

VisualizerCommandOBB::VisualizerCommandOBB(const CollisionVolumeOBB& S, const Vect& col)
{
	color = col;
	mat = Matrix(SCALE, S.GetMax() - S.GetMin())
		* Matrix(TRANS,
		(S.GetMin().X() + S.GetMax().X()) * 0.5f,
			(S.GetMin().Y() + S.GetMax().Y()) * 0.5f,
			(S.GetMin().Z() + S.GetMax().Z()) * 0.5f
		);
	mat *= S.GetWorld();
	center = S.GetWorldCenter();
}

VisualizerCommandOBB::~VisualizerCommandOBB()
{
	//	DebugMsg::out("Deleted VisualizerCommandOBB\n");
}

void VisualizerCommandOBB::execute()
{
	VisualizerAttorneyToCommand::RenderOBB(mat, center, color);
}