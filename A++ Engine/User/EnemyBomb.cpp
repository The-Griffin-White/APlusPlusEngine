#include "AzulCore.h"
#include "EnemyBomb.h"

#include "../Engine/SceneManager.h"

#include "../Engine/AlarmableManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"

#include "EnemyBombFactory.h"
#include "Tank.h"

EnemyBomb::EnemyBomb()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_Bomb = new GraphicsObject_TextureLight(ModelManager::Get("Sphere"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("Green"),
		LightColor, LightPos);

	SetColliderModel(pGObj_Bomb->getModel());

	fallSpeed = 1.5f;
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

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 15.0f);
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

void EnemyBomb::Update()
{
	pos += Vect(0, 0, 1) * fallSpeed * rot;
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_Bomb->SetWorld(world);

	this->UpdateCollisionData(world);
}

void EnemyBomb::Draw()
{
	pGObj_Bomb->Render(SceneManager::GetCurrentCamera());
}

void EnemyBomb::Alarm0()
{
	SubmitExit();
}