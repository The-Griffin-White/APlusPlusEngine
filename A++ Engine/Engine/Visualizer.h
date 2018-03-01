#ifndef _Visualizer
#define _Visualizer

#include <malloc.h>

#include "AzulCore.h"
#include "Align16.h"
#include "Colors.h"

class CollisionVolumeBSphere;
class VisualizerCommandBroker;

class Visualizer : public Align16
{
private:
	static Visualizer *ptrInstance;

	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	~Visualizer();

	static Visualizer& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Visualizer;
		return *ptrInstance;
	}
	static void Delete();

	VisualizerCommandBroker* cmdBroker;

	static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* WFUnitSphere;

	friend class VisualizerAttorneyToCommand;
	void privRenderBSphere(Matrix& S, const Vect& col);

	void privDraw();

public:
	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR);

	static void Draw() { Instance().privDraw(); };

};

#endif