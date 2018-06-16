#include "APPECore.h"
#include "EnemyBomb.h"

#include "SceneManager.h"

#include "AlarmableManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

#include "EnemyBombFactory.h"
#include "Tank.h"

EnemyBomb::EnemyBomb()
{
	pGObj_Bomb = new GraphicsObject_ColorNoTexture(ModelManager::Get("Sphere"));
	pGObj_Bomb->SetColor(Colors::Green);

	SetColliderModel(pGObj_Bomb->getModel(), CollisionModels::OBB);

	fallSpeed = 4.0f;
}

EnemyBomb::~EnemyBomb()
{
	DebugMsg::out("Deleted Bomb\n");
}

void EnemyBomb::Initialize(const Vect& Pos, const Matrix& Rot)
{
	Matrix world;
	scale.set(SCALE, 1.5f, 1.5f, 1.5f);
	rot = Rot;
	pos.set(Pos);
	world = scale * rot * Matrix(TRANS, pos);
	pGObj_Bomb->SetWorld(world);

	this->SubmitEntry();
}

void EnemyBomb::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Collidable::CollisionRegistration<EnemyBomb>(this);

	DebugMsg::out("EnemyBomb Alarm0 registered during sceneentry\n");
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 8.0f);
}

void EnemyBomb::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<EnemyBomb>(this);

	EnemyBombFactory::RecycleBomb(this);
}

void EnemyBomb::Collision(Tank* p)
{
	p;
	SubmitExit();
}

void EnemyBomb::Collision()
{
}

void EnemyBomb::TerrainCollision()
{
	SubmitExit();
}

void EnemyBomb::Update()
{
	pos += Vect(0, 0, 1) * fallSpeed * rot;
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_Bomb->SetWorld(world);

	this->UpdateCollisionData(world);
}

void EnemyBomb::Draw()
{
	pGObj_Bomb->Render();
}

void EnemyBomb::Alarm0()
{
	SubmitExit();
}