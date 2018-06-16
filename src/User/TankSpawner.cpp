#include "TankSpawner.h"
#include "EnemyTankFactory.h"

#include "SceneManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

#include "Bomb.h"

TankSpawner::TankSpawner(const int& x, const int& z, const int& r, const float& t)
	: xpos(x), zpos(z), range(r), time(t)
{
	health = MAX_HEALTH;

	pGObj = new GraphicsObject_TextureLight(ModelManager::Get("Cottage"));
	pGObj->SetTexture(TextureManager::Get("CottageTex1"), 0);
	pGObj->SetTexture(TextureManager::Get("CottageTex2"), 1);
	pGObj->SetTexture(TextureManager::Get("CottageTex3"), 2);
	pGObj->SetTexture(TextureManager::Get("CottageTex4"), 3);

	int randx = rand() % xpos + range;
	int randz = rand() % zpos + range;
	EnemyTankFactory::CreateEnemyTank(Vect((float)randx, 10, (float)randz));

	Matrix scale = Matrix(SCALE, 2.5f, 2.5f, 2.5f);
	Matrix rot = Matrix(IDENTITY);
	Vect pos = Vect((float)randx, 0, (float)randz);
	Matrix mPos = Matrix(TRANS, pos);
	Matrix world = scale * rot * mPos;
	pGObj->SetWorld(world);

	SetColliderModel(pGObj->getModel(), CollisionModels::AABB);

	this->UpdateCollisionData(world);

	Vect newUp;
	SceneManager::GetTerrainVector(this, newUp);
	Vect fwd = rot.get(ROW_2);
	Vect side = newUp.cross(fwd);
	fwd = side.cross(newUp);

	newUp.norm();
	newUp.set(newUp.X(), newUp.Y(), newUp.Z(), 0);
	fwd.norm();
	fwd.set(fwd.X(), fwd.Y(), fwd.Z(), 0);
	side.norm();
	side.set(side.X(), side.Y(), side.Z(), 0);

	rot = Matrix(IDENTITY);
	rot.set(ROW_2, fwd);
	rot.set(ROW_1, newUp);
	rot.set(ROW_0, side);

	float newY;
	SceneManager::GetTerrainHeight(this, newY);
	Vect adjustedPos = pos + Vect(0, newY, 0);
	mPos = Matrix(TRANS, adjustedPos);
	world = scale * rot * mPos;

	pGObj->SetWorld(world);
	this->UpdateCollisionData(world);

	SubmitEntry();
}

TankSpawner::~TankSpawner()
{
	delete pGObj;
}

void TankSpawner::SceneEntry()
{
	DebugMsg::out("TankSpawner Alarm0 registered during sceneentry\n");
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);

	Drawable::SubmitDrawRegistration();

	Collidable::CollisionRegistration<TankSpawner>(this);
	active = true;
}

void TankSpawner::SceneExit()
{
	Alarmable::DeregisterAll();

	Drawable::SubmitDrawDeregistration();

	Collidable::CollisionDeregistration<TankSpawner>(this);
	active = false;
}

void TankSpawner::Alarm0()
{
	int randx = rand() % xpos + range;
	int randz = rand() % zpos + range;
	EnemyTankFactory::CreateEnemyTank(Vect((float)randx, 10, (float)randz));
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_1, 0.01f);
}

void TankSpawner::Alarm1()
{
	DebugMsg::out("TankSpawner Alarm0 registered during alarm1\n");
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}

void TankSpawner::Draw()
{
	pGObj->Render();
}

void TankSpawner::Collision(Bomb*)
{
	--health;
	if (health <= 0)
	{
		this->SubmitExit();
	}
}