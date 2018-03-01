#include "SecondDemoScene.h"
#include "../Engine/APlusPlusEngine.h"
#include "../Engine/SceneManager.h"

#include "SpaceFrigate.h"
#include "Tank.h"

#include "BombFactory.h"

void SecondDemoScene::Initialize()
{
	APlusPlusEngine::SetBackgroundColor(0, 0, 0.8f, 1);

//---------------------------------------------------------------------------------------------------------
// Create the objects in this scene
//---------------------------------------------------------------------------------------------------------
	spaceship = new SpaceFrigate;
	spaceship->Initialize();

	tank = new Tank;
	tank->Initialize();

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

SecondDemoScene::~SecondDemoScene()
{
	BombFactory::RecallBomb();

	delete spaceship;
	delete tank;
}