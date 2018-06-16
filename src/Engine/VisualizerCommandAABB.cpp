#include "VisualizerCommandAABB.h"
#include "CollisionVolumeAABB.h"
#include "VisualizerAttorneyToCommand.h"

VisualizerCommandAABB::VisualizerCommandAABB(const CollisionVolumeAABB& S, const Vect& col)
{
	color = col;
	mat = Matrix(SCALE, S.GetMax() - S.GetMin()) 
		* Matrix(TRANS, 
		(S.GetMin().X() + S.GetMax().X()) / 2,
			(S.GetMin().Y() + S.GetMax().Y()) / 2,
			(S.GetMin().Z() + S.GetMax().Z()) / 2
		);
	center = S.GetWorldCenter();
}

VisualizerCommandAABB::VisualizerCommandAABB(const Vect& min, const Vect& max, const Vect& col)
{
	color = col;
	mat = Matrix(SCALE, (max - min))		// max - min
		* Matrix(TRANS,
		(min.X() + max.X()) / 2,
			(min.Y() + max.Y()) / 2,
			(min.Z() + max.Z()) / 2
		);
	center = min + ((max - min) * 0.5f);
}

VisualizerCommandAABB::~VisualizerCommandAABB()
{
//	DebugMsg::out("Deleted VisualizerCommandAABB\n");
}

void VisualizerCommandAABB::execute()
{
	VisualizerAttorneyToCommand::RenderAABB(mat, center, color);
}