#include "Visualizer.h"

#include "ModelManager.h"
#include "ShaderManager.h"

#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandBSphere.h"
#include "VisualizerCommandAABB.h"
#include "VisualizerCommandOBB.h"
#include "VisualizerCommandBroker.h"

#include "SceneManager.h"
#include "Collidable.h"

Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Colors::Aqua;

Visualizer::Visualizer()
{
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"));
	WFUnitSphere->SetColor(DEFAULT_COLOR);

	WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Box"));
	WFUnitBox->SetColor(DEFAULT_COLOR);

	cmdBroker = new VisualizerCommandBroker;
}

void Visualizer::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

Visualizer::~Visualizer()
{
	// This is for when the broker is added i guess
	delete cmdBroker;
	delete WFUnitSphere;
	delete WFUnitBox;
}

void Visualizer::Delete()
{
	// This is for when the broker is added i guess
	Instance().cmdBroker->Delete();
}

void Visualizer::ShowCollisionBSphere(const Collidable* c, const Vect& col)
{
	Visualizer::ShowBSphere(*c->GetCollisionBSphere(), col);
};

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col)
{
	WFUnitSphere->SetColor(col);
	WFUnitSphere->SetWorld(S);
	WFUnitSphere->Render();
}
void Visualizer::privRenderAABB(Matrix& S, Vect&, const Vect& col)
{
	WFUnitBox->SetColor(col);
	WFUnitBox->SetWorld(S);
	WFUnitBox->Render();
	// set up our center dot...
	//	Matrix world = Matrix(SCALE, 7.0f, 7.0f, 7.0f) * Matrix(IDENTITY) * Matrix(TRANS, c);
	//	WFUnitBox->SetWorld(world);
	//	WFUnitBox->Render(SceneManager::GetCurrentCamera());
}
void Visualizer::privRenderOBB(Matrix& S, Vect& c, const Vect& col)
{
	WFUnitBox->SetColor(col);
	WFUnitBox->SetWorld(S);
	WFUnitBox->Render();
	// set up our center dot...
	Matrix world = Matrix(SCALE, 7.0f, 7.0f, 7.0f) * Matrix(IDENTITY) * Matrix(TRANS, c);
	WFUnitBox->SetWorld(world);
	WFUnitBox->Render();
}

void Visualizer::ShowCollisionVolume(const Collidable* c, const Vect& col)
{
	c->GetCollisionVolume().DebugView(col);
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	Instance().cmdBroker->AddCommand(new VisualizerCommandBSphere(S, col));
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& S, const Vect& col)
{
	Instance().cmdBroker->AddCommand(new VisualizerCommandAABB(S, col));
}

void Visualizer::ShowAABB(const Vect& min, const Vect& max, const Vect& col)
{
	Instance().cmdBroker->AddCommand(new VisualizerCommandAABB(min, max, col));
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& S, const Vect& col)
{
	Instance().cmdBroker->AddCommand(new VisualizerCommandOBB(S, col));
}

void Visualizer::privDraw()
{
	cmdBroker->ExecuteCommands();
}