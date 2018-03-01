#include "MovementDemoScene.h"
#include "AzulCore.h"

#include "../Engine/APlusPlusEngine.h"
#include "../Engine/SceneManager.h"

#include "../Engine/CameraManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/ShaderManager.h"

#include "SpaceFrigate.h"
#include "Axis.h"
#include "Plane.h"
#include "Tank.h"
#include "GodCam.h"
#include "EnemyShip.h"
#include "EnemyTank.h"

#include "BombFactory.h"
#include "Bomb.h"

MovementDemoScene::MovementDemoScene()
{
	plane = nullptr;
	axis = nullptr;
	spaceship = nullptr;
	pCam3D = nullptr;
}
void MovementDemoScene::Initialize()
{
	//---------------------------------------------------------------------------------------------------------
	// Create the objects in this scene
	//---------------------------------------------------------------------------------------------------------
	
//	spaceship = new SpaceFrigate;
//	spaceship->Initialize();

	tank = new Tank;
	tank->Initialize();

	enemytank = new EnemyTank;
	enemytank->Initialize();

//	testShip = new EnemyShip;
//	testShip->Initialize();

//	pGodCam = new GodCam;
//	pGodCam->Initialize();

	axis = new Axis;
	axis->Initialize();

	plane = new Plane;
	plane->Initialize();

//	SetCollisionPair<SpaceFrigate, EnemyShip>();
	SetCollisionPair<Bomb, EnemyShip>();
	SetCollisionPair<Bomb, EnemyTank>();

	// Creating matrices for Axis and Plane placement

	//---------------------------------------------------------------------------------------------------------
	// Setup the current 3D perspective Camera
	//---------------------------------------------------------------------------------------------------------

	//	pCam3D = new Camera(Camera::Type::PERSPECTIVE_3D);
	//	CameraManager::Load(pCam3D);
	pCam3D = SceneManager::GetCurrentCamera();

	pCam3D->setViewport(0, 0, APlusPlusEngine::GetWindowWidth(), APlusPlusEngine::GetWindowHeight());
	pCam3D->setPerspective(35.0f, float(APlusPlusEngine::GetWindowWidth()) / float(APlusPlusEngine::GetWindowHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	pCam3D->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	pCam3D->updateCamera();  // Note: if the camera moves/changes, we need to call update again
}

MovementDemoScene::~MovementDemoScene()
{
	BombFactory::RecallBomb();

//	delete pGodCam;
//	delete spaceship;
	delete tank;
	delete enemytank;
	delete axis;
	delete plane;
}

void MovementDemoScene::Update()
{
	tank->GetPos();
}

void MovementDemoScene::Draw()
{
}