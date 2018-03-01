#include "AzulCore.h"
#include "EnemyShip.h"

#include "../Engine/SceneManager.h"

#include "../Engine/AlarmableManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"
#include "../Engine/Visualizer.h"
#include "../Engine/CollisionVolumeBSphere.h"

#include "SpaceFrigate.h"
#include "Bomb.h"
#include "Tank.h"
#include "EnemyShipFactory.h"

EnemyShip::EnemyShip()
{
	speed = 0.6f;

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("space_frigate"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("Green"),
		LightColor, LightPos);

	SetColliderModel(pGObj_SpaceFrigateLight->getModel());
}

void EnemyShip::Initialize()
{
	// Spaceship matrix
	Matrix world;
	ShipScale.set(SCALE, 0.3f, 0.3f, 0.3f);
	ShipRot.set(IDENTITY);
	ShipPos.set(40, 20, 40);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);
	this->UpdateCollisionData(world);

	lookAt = Vect(0, 0, 0);

	GameObject::SubmitEntry();
}

void EnemyShip::Initialize(const Vect& inPos)
{
	// Spaceship matrix
	Matrix world;
	ShipScale.set(SCALE, 0.3f, 0.3f, 0.3f);
	ShipRot.set(IDENTITY);
	ShipPos = inPos;
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);
	this->UpdateCollisionData(world);

	lookAt = Vect(0, 0, 0);

	GameObject::SubmitEntry();
}

void EnemyShip::InputPos(const Vect& inPos)
{
	lookAt = inPos;
}

EnemyShip::~EnemyShip()
{
	DebugMsg::out("Deleted EnemyShip\n");
}

void EnemyShip::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	
	Collidable::CollisionRegistration<EnemyShip>(this);
}

void EnemyShip::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Collidable::CollisionDeregistration<EnemyShip>(this);

	EnemyShipFactory::RecycleEnemyShip(this);
}

void EnemyShip::Update()
{
	// Turret adjust matrix
	Vect vDir = lookAt - ShipPos;
	vDir.norm();
	vDir.W() = 0;
	ShipRot.set(ROW_2, vDir);
	Vect side = Vect(0, 1, 0).cross(vDir);
	side.norm();
	side.W() = 0;
	ShipRot.set(ROW_0, side);
	Vect up = vDir.cross(side);
	up.norm();
	up.W() = 0;
	ShipRot.set(ROW_1, up);
	ShipPos += Vect(0, 0, 1) * ShipRot * speed;
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	this->UpdateCollisionData(world);	
}

void EnemyShip::Draw()
{
	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentCamera());
}

void EnemyShip::Collision(SpaceFrigate* p)
{
	p;
}

void EnemyShip::Collision(Bomb* p)
{
	p;
	SubmitExit();
}

void EnemyShip::Collision(Tank* p)
{
	p;
	SubmitExit();
}

void EnemyShip::Collision()
{
	//idk
}
