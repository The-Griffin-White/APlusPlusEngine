#include "APPECore.h"
#include "Tank.h"

#include "SceneManager.h"

#include "AlarmableManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "SpriteFactory.h"
#include "Sprite.h"

#include "EnemyBomb.h"
#include "EnemyShip.h"
#include "BombFactory.h"
#include "EnemyTankFactory.h"
#include "EnemyShipFactory.h"
#include "PlayerManager.h"

Tank::Tank()
{
	FirstPersonOffset = Vect(0, 10, -15);
	FirstPersonLookAt = Vect(0, 10, 10);
	ThirdPersonOffset = Vect(0, 30, -80);
	ThirdPersonLookAt = Vect(0, 10, 50);

	camOffset = &ThirdPersonOffset;
	camLookAt = &ThirdPersonLookAt;

	turretRotAngle = 0.03f;
	tankRotAngle = 0.05f;
	tankSpeed = 0.5f;

	pGObj_t99Turret = new GraphicsObject_TextureLight(ModelManager::Get("Turret"));
	pGObj_t99Turret->SetTexture(TextureManager::Get("Body"));

	pGObj_t99Body = new GraphicsObject_TextureLight(ModelManager::Get("Body"));
	pGObj_t99Body->SetTexture(TextureManager::Get("Body"), 0);
	pGObj_t99Body->SetTexture(TextureManager::Get("Track"), 1);
	pGObj_t99Body->SetTexture(TextureManager::Get("Track"), 2);

	SetColliderModel(pGObj_t99Body->getModel(), CollisionModels::OBB);

	//*
	xhair = SpriteFactory::CreateSprite(TextureManager::Get("xhair"), new Rect(0.0f, 0.0f, 150.0f, 150.0f));
	xhair->Pos(660, 425);
	xhairScale = 1.0f;
	xhair->Scale(xhairScale);
	//*/
}

void Tank::Initialize()
{
	currHealth = MaxHealth;
	bCanFire = true;
	xhairScale = 1.0f;
	xhair->Scale(xhairScale);

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

	degrees = 0;

	this->SubmitEntry();
}

void Tank::Initialize(const Vect& inPos)
{
	currHealth = MaxHealth;
	bCanFire = true;
	xhairScale = 1.0f;
	xhair->Scale(xhairScale);

	// Body matrix
	Matrix world;
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	rot.set(IDENTITY);
	pos = inPos;
	world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);
	this->UpdateCollisionData(world);

	// update with terrain info...
	float newY;
	bool overTerrain = SceneManager::GetTerrainHeight(this, newY);
	if (overTerrain) pos += Vect(0, newY, 0);

	world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);
	this->UpdateCollisionData(world);

	// Turret matrix
	scale.set(SCALE, 0.5f, 0.5f, 0.5f);
	turretRot = rot;
	turretPos = pos + Vect(0, 6, 0);
	world = scale * turretRot * Matrix(TRANS, turretPos);
	pGObj_t99Turret->SetWorld(world);

	degrees = 0;

	this->SubmitEntry();
}

Tank::~Tank()
{
	DebugMsg::out("Deleted Tank\n");
	delete xhair;
	delete pGObj_t99Body;
	delete pGObj_t99Turret;
}

void Tank::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_ARROW_UP, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_ARROW_DOWN, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	
	Collidable::CollisionRegistration<Tank>(this);
	xhair->SubmitRegistration();
}

void Tank::SceneExit()
{
	Alarmable::DeregisterAll();

	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_ARROW_UP, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_ARROW_DOWN, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);

	Collidable::CollisionDeregistration<Tank>(this);
	xhair->SubmitDeregistration();
}

const Vect& Tank::GetPos() const
{
	return pos;
}

void Tank::ChangeUpVector(Vect up)
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
}

void Tank::Update()
{
	Vect newUp;
	bool overTerrain = SceneManager::GetTerrainVector(this, newUp);
	if (overTerrain) this->ChangeUpVector(newUp);

	if (!bCanFire)
	{
		xhairScale += 0.005f;
		xhair->Scale(xhairScale);
	}

	// Body adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGObj_t99Body->SetWorld(world);

	this->UpdateCollisionData(world);

	// Turret adjust matrix
	world = scale * turretRot * Matrix(TRANS, turretPos);
	pGObj_t99Turret->SetWorld(world);
	
	// Placing the camera relative to the tank
	Matrix TankRotPos = turretRot * Matrix(TRANS, turretPos);  // This is the worldmat without scaling
	Vect vNewCamPos = *camLookAt * TankRotPos;		// This moves the cam position relative to tank's position and rotation
	Vect vNewLookAt = *camOffset * TankRotPos;   // This moves the look-at point relative to tank's position and rotation
	SceneManager::GetCurrentCamera()->setOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	SceneManager::GetCurrentCamera()->updateCamera();
}

void Tank::Draw()
{
	pGObj_t99Turret->Render();
	pGObj_t99Body->Render();
}

void Tank::Collision(EnemyShip* p)
{
//	currHealth -= 2;
	if (currHealth < 0)
	{
		PlayerManager::DecrementLives();
	}
	p;
}

void Tank::Collision(EnemyBomb* p)
{
//	currHealth -= 1;
	if (currHealth < 0)
	{
		PlayerManager::DecrementLives();
	}
	p;
}

void Tank::Collision()
{
}

void Tank::Alarm0()
{
	bCanFire = true;
	xhairScale = 1.0f;
	xhair->Scale(xhairScale);
}

void Tank::SetRespawnAlarm()
{
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_1, 0.5f);
}

void Tank::Alarm1()
{
	PlayerManager::SpawnTank();
}

void Tank::KeyPressed(APPE_KEY k)
{
	Vect turretLookAt;
	Vect vDir;
	Vect side;
	Vect up;

	switch (k)
	{
	case APPE_KEY::KEY_Q:
		camOffset = &FirstPersonOffset;
		camLookAt = &FirstPersonLookAt;
		turretRotAngle = 0.01f;
		xhair->Pos(660, 400);
		break;
	case APPE_KEY::KEY_E:
		camOffset = &ThirdPersonOffset;
		camLookAt = &ThirdPersonLookAt;
		turretRotAngle = 0.03f;
		xhair->Pos(660, 425);
		break;
	case APPE_KEY::KEY_V:
		if (bCanFire)
		{
			bCanFire = false;
			DebugMsg::out("Tank Alarm0 registered during fire input\n");
			SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
			BombFactory::CreateBomb(turretPos + Vect(0, 2, 0), turretRot);
			xhairScale = 0.5f;
			xhair->Scale(xhairScale);
		}
		break;
	case APPE_KEY::KEY_W:
		pos += Vect(0, 0, 1) * rot * tankSpeed;
		turretPos = pos + Vect(0, 6, 0);
		EnemyTankFactory::UpdateTarget(turretPos);
		EnemyShipFactory::UpdateTarget(turretPos);
		break;
	case APPE_KEY::KEY_A:
		rot *= Matrix(ROT_Y, tankRotAngle);
		turretRot *= Matrix(ROT_Y, turretRotAngle);
		break;
	case APPE_KEY::KEY_S:
		pos += Vect(0, 0, 1) * rot * -tankSpeed;
		turretPos = pos + Vect(0, 6, 0);
		EnemyTankFactory::UpdateTarget(pos);
		EnemyShipFactory::UpdateTarget(turretPos);
		break;
	case APPE_KEY::KEY_D:
		rot *= Matrix(ROT_Y, -tankRotAngle);
		turretRot *= Matrix(ROT_Y, -turretRotAngle);
		break;
	case APPE_KEY::KEY_ARROW_LEFT:
		turretRot *= Matrix(ROT_Y, turretRotAngle);
		break;
	case APPE_KEY::KEY_ARROW_RIGHT:
		turretRot *= Matrix(ROT_Y, -turretRotAngle);
		break;
	case APPE_KEY::KEY_ARROW_UP:
		if (degrees < maxUp)
		{
			++degrees;

			turretLookAt = turretPos + Vect(0, 0, 10) * turretRot;
			turretLookAt += Vect(0, 1, 0) * turretRot * (2 * turretRotAngle);
			vDir = turretLookAt - turretPos;
			vDir.norm();
			vDir.W() = 0;
			turretRot.set(ROW_2, vDir);
			side = Vect(0, 1, 0).cross(vDir);
			side.norm();
			side.W() = 0;
			turretRot.set(ROW_0, side);
			up = vDir.cross(side);
			up.norm();
			up.W() = 0;
			turretRot.set(ROW_1, up);
		}
		break;
	case APPE_KEY::KEY_ARROW_DOWN:
		if (degrees > maxDown)
		{
			--degrees;

			turretLookAt = turretPos + Vect(0, 0, 10) * turretRot;
			turretLookAt += Vect(0, 1, 0) * turretRot * (2 * -turretRotAngle);
			vDir = turretLookAt - turretPos;
			vDir.norm();
			vDir.W() = 0;
			turretRot.set(ROW_2, vDir);
			side = Vect(0, 1, 0).cross(vDir);
			side.norm();
			side.W() = 0;
			turretRot.set(ROW_0, side);
			up = vDir.cross(side);
			up.norm();
			up.W() = 0;
			turretRot.set(ROW_1, up);
		}
		break;
	}
}