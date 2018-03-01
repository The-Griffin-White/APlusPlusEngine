#include "AzulCore.h"
#include "Bomb.h"

#include "../Engine/SceneManager.h"

#include "../Engine/AlarmableManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"

#include "BombFactory.h"
#include "EnemyShip.h"

Bomb::Bomb()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_Bomb = new GraphicsObject_TextureLight(ModelManager::Get("Sphere"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("Orange"),
		LightColor, LightPos);

	SetColliderModel(pGObj_Bomb->getModel());

	fallSpeed = 1.5f;
}

Bomb::~Bomb()
{
	DebugMsg::out("Deleted Bomb\n");
}

void Bomb::Initialize(const Vect& Pos, const Matrix& Rot)
{
	Matrix world;
	scale.set(SCALE, 1.5f, 1.5f, 1.5f);
	rot = Rot;
	pos.set(Pos);
	world = scale * rot * Matrix(TRANS, pos);
	pGObj_Bomb->SetWorld(world);

	this->SubmitEntry();
}

void Bomb::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Collidable::CollisionRegistration<Bomb>(this);

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 15.0f);
}

void Bomb::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<Bomb>(this);

	BombFactory::RecycleBomb(this);
}

void Bomb::Collision(EnemyShip* p)
{
	p;
	SubmitExit();
}

void Bomb::Collision(EnemyTank* p)
{
	p;
	SubmitExit();
}

void Bomb::Collision()
{
}

void Bomb::Update()
{
	pos += Vect(0, 0, 1) * fallSpeed * rot;
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_Bomb->SetWorld(world);

	this->UpdateCollisionData(world);
}

void Bomb::Draw()
{
	pGObj_Bomb->Render(SceneManager::GetCurrentCamera());
}

void Bomb::Alarm0()
{
	SceneExit();
}