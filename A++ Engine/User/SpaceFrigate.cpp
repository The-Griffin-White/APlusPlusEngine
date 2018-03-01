#include "AzulCore.h"
#include "SpaceFrigate.h"

#include "../Engine/SceneManager.h"

#include "../Engine/AlarmableManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"
#include "../Engine/Visualizer.h"
#include "../Engine/CollisionVolumeBSphere.h"

#include "BombFactory.h"
#include "EnemyShip.h"


SpaceFrigate::SpaceFrigate()
{
	CamShipOffset = Vect(0, 70, -150);
	CamLookAt = Vect(0, 0, 0);

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("space_frigate"),
		ShaderManager::Get("textureLightRender"),
		TextureManager::Get("space_frigate"),
		LightColor, LightPos);

	SetColliderModel(pGObj_SpaceFrigateLight->getModel());
	registered = false;
}

void SpaceFrigate::Initialize()
{
	// Spaceship matrix
	Matrix world;
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 20, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	BsphereToggle = false;
	canFire = true;

	GameObject::SubmitEntry();
}

void SpaceFrigate::SceneEntry() 
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_1, 3.0f);

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_P, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	RegisterKeys();

	Collidable::CollisionRegistration<SpaceFrigate>(this);
}

void SpaceFrigate::RegisterKeys()
{
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, Inputable::INPUT_EVENT_TYPE::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_BACKSPACE, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	registered = true;
}

void SpaceFrigate::SceneExit() 
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Alarmable::DeregisterAll();

	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_P, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	DeregisterKeys();

	Collidable::CollisionDeregistration<SpaceFrigate>(this);
}

void SpaceFrigate::DeregisterKeys()
{
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, Inputable::INPUT_EVENT_TYPE::KEY_RELEASE);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_BACKSPACE, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	registered = false;
}

SpaceFrigate::~SpaceFrigate()
{
	DebugMsg::out("Deleted SpaceFrigate\n");
}

void SpaceFrigate::Collision(EnemyShip* p)
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


void SpaceFrigate::Update()
{
	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	/*
	// Placing the camera relative to the spaceship
	Matrix ShipRotPos = ShipRot * Matrix(TRANS, ShipPos);  // This is the worldmat without scaling
	Vect vNewCamPos = CamLookAt * ShipRotPos;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = CamShipOffset * ShipRotPos;   // This moves the look-at point relative to ship's position and rotation
	SceneManager::GetCurrentCamera()->setOrientAndPosition( Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	SceneManager::GetCurrentCamera()->updateCamera();
	//*/

	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_SpaceFrigateLight->getModel()->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_SpaceFrigateLight->getModel()->getCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	this->UpdateCollisionData(world);
}

void SpaceFrigate::Draw()
{
	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentCamera());
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

void SpaceFrigate::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_O:
		if (registered)
			DeregisterKeys();
		break;
	case AZUL_KEY::KEY_P:
		if (!registered)
			RegisterKeys();
		break;
	case AZUL_KEY::KEY_SPACE:
		BsphereToggle = true;
		break;
	case AZUL_KEY::KEY_V:
		if (canFire)
		{
			canFire = false;
			SubmitAlarmRegistration(AlarmableManager::ALARM_2, 0.5f);
			BombFactory::CreateBomb(ShipPos, ShipRot);
		}
		break;
	case AZUL_KEY::KEY_W:
		ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
		break;
	case AZUL_KEY::KEY_A:
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
		break;
	case AZUL_KEY::KEY_S:
		ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
		break;
	case AZUL_KEY::KEY_D:
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
		break;
	case AZUL_KEY::KEY_BACKSPACE:
		this->SubmitExit();
		break;
	}
}

void SpaceFrigate::KeyReleased(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		BsphereToggle = false;
		break;
	}
}