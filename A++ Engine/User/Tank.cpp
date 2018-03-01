#include "AzulCore.h"
#include "Tank.h"

#include "../Engine/SceneManager.h"

#include "../Engine/AlarmableManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"

#include "EnemyBomb.h"
#include "EnemyShip.h"
#include "BombFactory.h"
#include "EnemyTankFactory.h"
#include "EnemyShipFactory.h"

Tank::Tank()
{
	FirstPersonOffset = Vect(0, 10, -15);
	FirstPersonLookAt = Vect(0, 10, 10);
	ThirdPersonOffset = Vect(0, 30, -80);
	ThirdPersonLookAt = Vect(0, 10, 50);

	camOffset = &ThirdPersonOffset;
	camLookAt = &ThirdPersonLookAt;

	turretRotAngle = 0.05f;
	tankRotAngle = 0.05f;
	tankSpeed = 0.5f;

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_t99Turret = new GraphicsObject_TextureLight(ModelManager::Get("Turret"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("Body"),
		LightColor, LightPos);

	pGObj_t99Body = new GraphicsObject_TextureLight(ModelManager::Get("Body"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("Body"),
		TextureManager::Get("Track"),
		LightColor, LightPos);

	SetColliderModel(pGObj_t99Body->getModel());
}

void Tank::Initialize()
{
	currHealth = MaxHealth;

	// Body matrix
	Matrix world;
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	rot.set(IDENTITY);
	pos.set(0, 1, 0);
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

void Tank::Initialize(const Vect& inPos)
{
	currHealth = MaxHealth;

	// Body matrix
	Matrix world;
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	rot.set(IDENTITY);
	pos = inPos;
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

Tank::~Tank()
{
	DebugMsg::out("Deleted Tank\n");
}

void Tank::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	
	Collidable::CollisionRegistration<Tank>(this);
}

void Tank::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);

	Collidable::CollisionDeregistration<Tank>(this);
}

const Vect& Tank::GetPos() const
{
	return pos;
}

void Tank::Update()
{
	// Body adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);

	// Turret adjust matrix
	world = scale * turretRot * Matrix(TRANS, turretPos);
	pGObj_t99Turret->SetWorld(world);
	
	// Placing the camera relative to the tank
	Matrix TankRotPos = turretRot * Matrix(TRANS, turretPos);  // This is the worldmat without scaling
	Vect vNewCamPos = *camLookAt * TankRotPos;		// This moves the cam position relative to tank's position and rotation
	Vect vNewLookAt = *camOffset * TankRotPos;   // This moves the look-at point relative to tank's position and rotation
	SceneManager::GetCurrentCamera()->setOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	SceneManager::GetCurrentCamera()->updateCamera();

	this->UpdateCollisionData(world);
}

void Tank::Draw()
{
	pGObj_t99Turret->Render(SceneManager::GetCurrentCamera());
	pGObj_t99Body->Render(SceneManager::GetCurrentCamera());
}

void Tank::Collision(EnemyShip* p)
{
	currHealth -= 2;
	if (currHealth < 0)
		SubmitExit();
	p;
}

void Tank::Collision(EnemyBomb* p)
{
	currHealth -= 1;
	if (currHealth < 0)
		SubmitExit();
	p;
}

void Tank::Collision()
{
}

void Tank::Alarm0()
{
	bCanFire = true;
}

void Tank::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_Q:
		camOffset = &FirstPersonOffset;
		camLookAt = &FirstPersonLookAt;
		break;
	case AZUL_KEY::KEY_E:
		camOffset = &ThirdPersonOffset;
		camLookAt = &ThirdPersonLookAt;
		break;
	case AZUL_KEY::KEY_V:
		if (bCanFire)
		{
			bCanFire = false;
			SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
			BombFactory::CreateBomb(turretPos, turretRot);
		}
		break;
	case AZUL_KEY::KEY_W:
		pos += Vect(0, 0, 1) * rot * tankSpeed;
		turretPos = pos + Vect(0, 6, 0);
		EnemyTankFactory::UpdateTarget(turretPos);
		EnemyShipFactory::UpdateTarget(turretPos);
		break;
	case AZUL_KEY::KEY_A:
		rot *= Matrix(ROT_Y, tankRotAngle);
		turretRot *= Matrix(ROT_Y, turretRotAngle);
		break;
	case AZUL_KEY::KEY_S:
		pos += Vect(0, 0, 1) * rot * -tankSpeed;
		turretPos = pos + Vect(0, 6, 0);
		EnemyTankFactory::UpdateTarget(pos);
		EnemyShipFactory::UpdateTarget(turretPos);
		break;
	case AZUL_KEY::KEY_D:
		rot *= Matrix(ROT_Y, -tankRotAngle);
		turretRot *= Matrix(ROT_Y, -turretRotAngle);
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		turretRot *= Matrix(ROT_Y, turretRotAngle);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		turretRot *= Matrix(ROT_Y, -turretRotAngle);
		break;
	}
}