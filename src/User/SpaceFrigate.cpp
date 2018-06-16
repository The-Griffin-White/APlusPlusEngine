#include "APPECore.h"
#include "SpaceFrigate.h"

#include "SceneManager.h"

#include "AlarmableManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "Visualizer.h"
#include "CollisionVolumeBSphere.h"

#include "TestShip.h"

#include "SFXManager.h"


SpaceFrigate::SpaceFrigate()
{
	CamShipOffset = Vect(0, 70, -150);
	CamLookAt = Vect(0, 0, 0);

	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("space_frigate"));
	pGObj_SpaceFrigateLight->SetTexture(TextureManager::Get("space_frigate"));
	pGObj_SpaceFrigateLight->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));

	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionModels::OBB);
	registered = false;
}

void SpaceFrigate::Initialize()
{
	newCell = false;

	// Spaceship matrix
	Matrix world;
	ShipScale.set(IDENTITY);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 20, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	canFire = true;

	// Placing the camera relative to the spaceship
	Matrix ShipRotPos = ShipRot * Matrix(TRANS, ShipPos);  // This is the worldmat without scaling
	Vect vNewCamPos = CamLookAt * ShipRotPos;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = CamShipOffset * ShipRotPos;   // This moves the look-at point relative to ship's position and rotation
	SceneManager::GetCurrentCamera()->setOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	SceneManager::GetCurrentCamera()->updateCamera();

	this->UpdateCollisionData(world);

	GameObject::SubmitEntry();
}

void SpaceFrigate::SceneEntry() 
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_1, 3.0f);

	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_P, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	RegisterKeys();

	Collidable::CollisionRegistration<SpaceFrigate>(this);
}

void SpaceFrigate::RegisterKeys()
{
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(APPE_KEY::KEY_BACKSPACE, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	registered = true;
}

void SpaceFrigate::SceneExit() 
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Alarmable::DeregisterAll();

	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_P, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	DeregisterKeys();

	Collidable::CollisionDeregistration<SpaceFrigate>(this);
}

void SpaceFrigate::DeregisterKeys()
{
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_BACKSPACE, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	registered = false;
}

SpaceFrigate::~SpaceFrigate()
{
	DebugMsg::out("Deleted SpaceFrigate\n");
	delete pGObj_SpaceFrigateLight;
}

void SpaceFrigate::Collision(TestShip* p)
{
	p;
//	DebugMsg::out("SpaceFrigate collided with EnemyShip\n");
}

void SpaceFrigate::Collision(Plane* p)
{
	p;
	DebugMsg::out("SpaceFrigate collided with Plane\n");
}

void SpaceFrigate::Collision()
{
	DebugMsg::out("SpaceFrigate collided with Itself\n");
}

void SpaceFrigate::ChangeUpVector(Vect up)
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

void SpaceFrigate::Update()
{
	Vect newUp;
	bool overTerrain = SceneManager::GetTerrainVector(this, newUp);
	if (overTerrain) this->ChangeUpVector(newUp);
	float newY;
	overTerrain = SceneManager::GetTerrainHeight(this, newY);
	Vect adjustedPos = ShipPos;
	if (overTerrain) adjustedPos += Vect(0, newY, 0);

	DebugMsg::out("ShipPos: %f  %f  %f\n", ShipPos.X(), ShipPos.Y(), ShipPos.Z());
	DebugMsg::out("adjustedPos: %f  %f  %f\n", adjustedPos.X(), adjustedPos.Y(), adjustedPos.Z());

	SFXManager::ChangePointLighting(0, ShipPos, 15, 0.5f * Vect(1, 1, 1),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	this->UpdateCollisionData(world);
}

void SpaceFrigate::Draw()
{
	pGObj_SpaceFrigateLight->Render();
}

void SpaceFrigate::Alarm0()
{
	DebugMsg::out("Alarm 0 called\n");
}

void SpaceFrigate::Alarm1()
{
	DebugMsg::out("Alarm 1 called\n");
}

void SpaceFrigate::Alarm2()
{
	canFire = true;
}

void SpaceFrigate::KeyPressed(APPE_KEY k)
{
	switch (k)
	{
	case APPE_KEY::KEY_O:
		if (registered)
			DeregisterKeys();
		break;
	case APPE_KEY::KEY_P:
		if (!registered)
			RegisterKeys();
		break;
	case APPE_KEY::KEY_W:
		ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
		break;
	case APPE_KEY::KEY_A:
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
		break;
	case APPE_KEY::KEY_S:
		ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
		break;
	case APPE_KEY::KEY_D:
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
		break;
	case APPE_KEY::KEY_BACKSPACE:
		this->SubmitExit();
		break;
	}
}

void SpaceFrigate::KeyReleased(APPE_KEY)
{
}