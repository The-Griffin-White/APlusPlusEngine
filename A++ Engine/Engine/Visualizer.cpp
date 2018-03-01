#include "Visualizer.h"

#include "ModelManager.h"
#include "ShaderManager.h"

#include "CollisionVolumeBSphere.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandBroker.h"

#include "SceneManager.h"

Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Colors::Aqua;

Visualizer::Visualizer()
{
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"),
		ShaderManager::Get("colorConstantRender"),
		DEFAULT_COLOR);

	cmdBroker = new VisualizerCommandBroker;
}

Visualizer::~Visualizer()
{
	// This is for when the broker is added i guess
	delete cmdBroker;
}

void Visualizer::Delete()
{
	// This is for when the broker is added i guess
	Instance().cmdBroker->Delete();
}

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col)
{
	WFUnitSphere->pWireColor->set(col);
	WFUnitSphere->SetWorld(S);
	WFUnitSphere->Render(SceneManager::GetCurrentCamera());
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	Instance().cmdBroker->AddCommand(new VisualizerCommand(S, col));
}

void Visualizer::privDraw()
{
	cmdBroker->ExecuteCommands();
}