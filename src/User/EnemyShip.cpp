#include "APPECore.h"
#include "EnemyShip.h"

#include "SceneManager.h"

#include "AlarmableManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "Visualizer.h"
#include "CollisionVolumeBSphere.h"

#include "SpaceFrigate.h"
#include "Bomb.h"
#include "Tank.h"
#include "EnemyShipFactory.h"
#include "ExplosionFactory.h"

EnemyShip::EnemyShip()
{
	speed = 2.0f;

	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("space_frigate"));
	pGObj_SpaceFrigateLight->SetTexture(TextureManager::Get("space_frigate"));

	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionModels::BSphere);
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

	float newY;
	bool overTerrain = SceneManager::GetTerrainHeight(this, newY);
	if (overTerrain) ShipPos += Vect(0, newY, 0);

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

	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<EnemyShip>(this);

	EnemyShipFactory::RecycleEnemyShip(this);
}

void EnemyShip::ChangeUpVector(Vect up)
{
	Vect fwd = ShipRot.get(ROW_2);
	Vect side = up.cross(fwd);
	fwd = side.cross(up);

	up.norm();
	up.set(up.X(), up.Y(), up.Z(), 0);
	fwd.norm();
	fwd.set(fwd.X(), fwd.Y(), fwd.Z(), 0);
	side.norm();
	side.set(side.X(), side.Y(), side.Z(), 0);

	ShipRot = Matrix(IDENTITY);
	ShipRot.set(ROW_2, fwd);
	ShipRot.set(ROW_1, up);
	ShipRot.set(ROW_0, side);
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

	Vect newUp;
	bool overTerrain = SceneManager::GetTerrainVector(this, newUp);
	if (overTerrain) this->ChangeUpVector(newUp);

	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	this->UpdateCollisionData(world);	
}

void EnemyShip::Draw()
{
	pGObj_SpaceFrigateLight->Render();
}

void EnemyShip::Collision(Bomb* p)
{
	p;
	ExplosionFactory::CreateExplosion(ShipPos);
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
