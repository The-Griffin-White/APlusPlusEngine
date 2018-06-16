#include "APPECore.h"
#include "EnemyTank.h"

#include "SceneManager.h"

#include "AlarmableManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

#include "EnemyBombFactory.h"
#include "EnemyTankFactory.h"

#include "ExplosionFactory.h"

EnemyTank::EnemyTank()
{
	lookAt = Vect(0, 0, 0);

	turretRotAngle = 0.01f;
	tankRotAngle = 0.001f;
	tankSpeed = 0.1f;

	pGObj_t99Turret = new GraphicsObject_TextureLight(ModelManager::Get("Turret"));
	pGObj_t99Turret->SetTexture(TextureManager::Get("Body"));

	pGObj_t99Body = new GraphicsObject_TextureLight(ModelManager::Get("Body"));
	pGObj_t99Body->SetTexture(TextureManager::Get("Body"), 0);
	pGObj_t99Body->SetTexture(TextureManager::Get("Track"), 1);
	pGObj_t99Body->SetTexture(TextureManager::Get("Track"), 2);

	SetColliderModel(pGObj_t99Body->getModel(), CollisionModels::AABB);
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
	this->UpdateCollisionData(world);

	// Turret matrix
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	turretRot = rot;
	turretPos = pos + Vect(0, 6, 0);
	world = scale * turretRot * Matrix(TRANS, turretPos);
	pGObj_t99Turret->SetWorld(world);

	float newY;
	bool overTerrain = SceneManager::GetTerrainHeight(this, newY);
	if (overTerrain) pos += Vect(0, newY, 0);

	world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Turret->SetWorld(world);
	this->UpdateCollisionData(world);
	
	this->SubmitEntry();
}

void EnemyTank::Initialize(const Vect& inPos)
{
	bCanFire = true;
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

	float newY;
	bool overTerrain = SceneManager::GetTerrainHeight(this, newY);
	if (overTerrain) pos += Vect(0, newY, 0);

	world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Turret->SetWorld(world);
	this->UpdateCollisionData(world);

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

	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<EnemyTank>(this);
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
	{
		ExplosionFactory::CreateExplosion(pos);
		EnemyTankFactory::RecycleEnemyTank(this);
		SubmitExit();
	}
	p;
}

void EnemyTank::Collision()
{
}

void EnemyTank::ChangeUpVector(Vect up)
{
	Vect fwd = rot.get(ROW_2);
	Vect side = up.cross(fwd);
	fwd = side.cross(up);

	up.norm();
	up.set(up.X(), up.Y(), up.Z(), 0);
	fwd.norm();
	fwd.set(fwd.X(), fwd.Y(), fwd.Z(), 0);
	side.norm();
	side.set(side.X(), side.Y(), side.Z(), 0);

	rot = Matrix(IDENTITY);
	rot.set(ROW_2, fwd);
	rot.set(ROW_1, up);
	rot.set(ROW_0, side);

	fwd = turretRot.get(ROW_2);
	side = up.cross(fwd);
	fwd = side.cross(up);

	up.set(up.X(), up.Y(), up.Z(), 0);
	fwd.set(fwd.X(), fwd.Y(), fwd.Z(), 0);
	side.set(side.X(), side.Y(), side.Z(), 0);

	turretRot = Matrix(IDENTITY);
	turretRot.set(ROW_2, fwd);
	turretRot.set(ROW_1, up);
	turretRot.set(ROW_0, side);
}

void EnemyTank::Update()
{
	Vect newUp;
	bool overTerrain = SceneManager::GetTerrainVector(this, newUp);
	if (overTerrain) this->ChangeUpVector(newUp);

	// Body adjust matrix
	rot *= Matrix(ROT_Y, tankRotAngle);
	pos += Vect(0, 0, 1) * rot * tankSpeed;
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);

	this->UpdateCollisionData(world);

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
		EnemyBombFactory::CreateBomb(turretPos + Vect(0, 2, 0), turretRot);
		bCanFire = false;
		DebugMsg::out("EnemyTank Alarm0 registered during updatecycle\n");
		Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
	}
}

void EnemyTank::Draw()
{
	pGObj_t99Turret->Render();
	pGObj_t99Body->Render();
}

void EnemyTank::Alarm0()
{
	bCanFire = true;
}