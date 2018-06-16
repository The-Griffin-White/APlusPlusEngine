#ifndef _VisualizerAttorneyToCommand
#define _VisualizerAttorneyToCommand

#include "Visualizer.h"

class VisualizerAttorneyToCommand
{
private:
	friend class VisualizerCommandBSphere;
	static void RenderBSphere(Matrix& S, const Vect& col) { Visualizer::Instance().privRenderBSphere(S, col); };
	friend class VisualizerCommandAABB;
	static void RenderAABB(Matrix& S, Vect& c, const Vect& col) { Visualizer::Instance().privRenderAABB(S, c, col); };
	friend class VisualizerCommandOBB;
	static void RenderOBB(Matrix& S, Vect& c, const Vect& col) { Visualizer::Instance().privRenderOBB(S, c, col); };
};

#endif _VisualizerAttorneyToCommand