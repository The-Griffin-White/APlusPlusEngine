#include "APPECore.h"
#include "Bomb.h"

#include "SceneManager.h"

#include "AlarmableManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

#include "BombFactory.h"
#include "EnemyShip.h"
#include "ShipSpawner.h"
#include "TankSpawner.h"

Bomb::Bomb()
{
	pGObj_Bomb = new GraphicsObject_ColorNoTexture(ModelManager::Get("Sphere"));
	pGObj_Bomb->SetColor(Colors::Orange);

	SetColliderModel(pGObj_Bomb->getModel(), CollisionModels::OBB);

	fallSpeed = 8.0f;
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

	lightNum = SFXManager::AssignPointLighting(pos, 15, 0.5f * Vect(1, 1, 1),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	this->SubmitEntry();
}

void Bomb::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	DebugMsg::out("Bomb Alarm0 registered during scenentry\n");
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 8.0f);
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_1, 0.2f);
}

void Bomb::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<Bomb>(this);

	SFXManager::DeactivatePointLight(lightNum);
}

void Bomb::Collision(EnemyShip*)
{

	BombFactory::RecycleBomb(this);
	SubmitExit();
}

void Bomb::Collision(EnemyTank*)
{

	BombFactory::RecycleBomb(this);
	SubmitExit();
}

void Bomb::Collision(TankSpawner*)
{

	BombFactory::RecycleBomb(this);
	SubmitExit();
}

void Bomb::Collision(ShipSpawner*)
{

	BombFactory::RecycleBomb(this);
	SubmitExit();
}

void Bomb::Collision()
{
}

void Bomb::TerrainCollision()
{

	BombFactory::RecycleBomb(this);
	SubmitExit();
}

void Bomb::Update()
{
	pos += Vect(0, 0, 1) * fallSpeed * rot;
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_Bomb->SetWorld(world);

	SFXManager::ChangePointLighting(lightNum, pos, 15, 0.5f * Vect(1, 1, 1),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	this->UpdateCollisionData(world);
}

void Bomb::Draw()
{
	pGObj_Bomb->Render();
}

void Bomb::Alarm0()
{
	BombFactory::RecycleBomb(this);
	SubmitExit();
}

void Bomb::Alarm1()
{
	Collidable::CollisionRegistration<Bomb>(this);
}