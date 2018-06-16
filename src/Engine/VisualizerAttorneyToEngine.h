#ifndef _VisualizerAttorneyToEngine
#define _VisualizerAttorneyToEngine

#include "Visualizer.h"

class VisualizerAttorneyToEngine
{
private:
	friend class APlusPlusEngine;
	static void Terminate() { Visualizer::Terminate(); };
};

#endif