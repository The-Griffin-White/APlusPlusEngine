#include "APPECore.h"
#include "TestShip.h"

#include "SceneManager.h"

#include "AlarmableManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "Visualizer.h"
#include "CollisionVolumeBSphere.h"

TestShip::TestShip()
{
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("space_frigate"));
	pGObj_SpaceFrigateLight->SetTexture(TextureManager::Get("space_frigate"));
	pGObj_SpaceFrigateLight->SetMaterial(Colors::Green, Colors::Blue, Vect(1, 1, 1, 100));

	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionModels::AABB);
}

void TestShip::Initialize()
{
	// Spaceship matrix
	Matrix ShipScale(IDENTITY);
	Matrix ShipRot(ROT_Y, 0.75f);
	Vect ShipPos = Vect(20, 20, 20);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	GameObject::SubmitEntry();
}

void TestShip::Initialize(const Vect& pos)
{
	// Spaceship matrix
	Matrix ShipScale(SCALE, 0.5f, 0.5f, 0.5f);
	Matrix ShipRot(ROT_Y, 0.75f);
	Vect ShipPos = pos;
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	GameObject::SubmitEntry();
}

void TestShip::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Collidable::CollisionRegistration<TestShip>(this);
}

void TestShip::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Collidable::CollisionDeregistration<TestShip>(this);
}

TestShip::~TestShip()
{
	DebugMsg::out("Deleted SpaceFrigate\n");
	delete pGObj_SpaceFrigateLight;
}

void TestShip::Collision(SpaceFrigate* p)
{
	p;
	//	DebugMsg::out("TestShip collided with SpaceFrigate\n");
}

void TestShip::Collision(Plane* p)
{
	p;
	DebugMsg::out("SpaceFrigate collided with Plane\n");
}

void TestShip::Collision()
{
	DebugMsg::out("TestShip collided with Itself\n");
}


void TestShip::Update()
{
	this->UpdateCollisionData(world);
}

void TestShip::Draw()
{
	pGObj_SpaceFrigateLight->Render();
}