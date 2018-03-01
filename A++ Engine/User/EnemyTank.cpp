#include "AzulCore.h"
#include "EnemyTank.h"

#include "../Engine/SceneManager.h"

#include "../Engine/AlarmableManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"

#include "EnemyBombFactory.h"
#include "EnemyTankFactory.h"

EnemyTank::EnemyTank()
{
	lookAt = Vect(0, 0, 0);

	turretRotAngle = 0.01f;
	tankRotAngle = 0.001f;
	tankSpeed = 0.1f;

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_t99Turret = new GraphicsObject_TextureLight(ModelManager::Get("Turret"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("Green"),
		LightColor, LightPos);

	pGObj_t99Body = new GraphicsObject_TextureLight(ModelManager::Get("Body"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("Body"),
		TextureManager::Get("Green"),
		LightColor, LightPos);

	SetColliderModel(pGObj_t99Body->getModel());
}

void EnemyTank::Initialize()
{
	currHealth = MaxHealth;
	// Body matrix
	Matrix world;
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	rot.set(IDENTITY);
	pos.set(100, 1, -100);
	world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);

	// Turret matrix
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	turretRot = rot;
	turretPos = pos + Vect(0, 6, 0);
	world = scale * turretRot * Matrix(TRANS, turretPos);
	pGObj_t99Turret->SetWorld(world);
	
	this->SubmitEntry();
}

void EnemyTank::Initialize(const Vect& inPos)
{
	currHealth = MaxHealth;
	// Body matrix
	Matrix world;
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	rot.set(IDENTITY);
	pos.set(inPos);
	world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);

	// Turret matrix
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	turretRot = rot;
	rot.set(IDENTITY);
	turretPos = pos + Vect(0, 6, 0);
	world = scale * turretRot * Matrix(TRANS, turretPos);
	pGObj_t99Turret->SetWorld(world);

	this->SubmitEntry();
}

EnemyTank::~EnemyTank()
{
	DebugMsg::out("Deleted EnemyTank\n");
}

void EnemyTank::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Collidable::CollisionRegistration<EnemyTank>(this);
}

void EnemyTank::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Collidable::CollisionDeregistration<EnemyTank>(this);

	EnemyTankFactory::RecycleEnemyTank(this);
}

void EnemyTank::InputPos(const Vect& inPos)
{
	lookAt = inPos;
}

void EnemyTank::Collision(Bomb* p)
{
//	DebugMsg::out("EnemyTank Hit!\n");
	currHealth -= 1;
	if (currHealth < 0)
		SubmitExit();
	p;
}

void EnemyTank::Collision()
{
}

void EnemyTank::Update()
{
	// Body adjust matrix
	rot *= Matrix(ROT_Y, tankRotAngle);
	pos += Vect(0, 0, 1) * rot * tankSpeed;
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);

	// Turret adjust matrix
	turretPos = pos + Vect(0, 6, 0);
	Vect vDir = lookAt - turretPos;
	vDir.norm();
	vDir.W() = 0;
	turretRot.set(ROW_2, vDir);
	Vect side = Vect(0, 1, 0).cross(vDir);
	side.norm();
	side.W() = 0;
	turretRot.set(ROW_0, side);
	Vect up = vDir.cross(side);
	up.norm();
	up.W() = 0;
	turretRot.set(ROW_1, up);
	world = scale * turretRot * Matrix(TRANS, turretPos);
	pGObj_t99Turret->SetWorld(world);

	if (bCanFire)
	{
		EnemyBombFactory::CreateBomb(turretPos, turretRot);
		bCanFire = false;
		Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
	}

	this->UpdateCollisionData(world);
}

void EnemyTank::Draw()
{
	pGObj_t99Turret->Render(SceneManager::GetCurrentCamera());
	pGObj_t99Body->Render(SceneManager::GetCurrentCamera());
}

void EnemyTank::Alarm0()
{
	bCanFire = true;
}