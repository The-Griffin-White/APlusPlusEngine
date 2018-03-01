#ifndef _VisualizerAttorneyToCommand
#define _VisualizerAttorneyToCommand

#include "Visualizer.h"

class VisualizerAttorneyToCommand
{
private:
	friend class VisualizerCommand;
	static void RenderBSphere(Matrix& S, const Vect& col) { Visualizer::Instance().privRenderBSphere(S, col); };
};

#endif _VisualizerAttorneyToCommand