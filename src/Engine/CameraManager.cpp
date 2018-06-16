#include "CameraManager.h"
#include "APPECore.h"

#include "APlusPlusEngine.h"

CameraManager::CameraManager()
{
	orthoCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	orthoCamera->setOrthographic(
		 1 * (float)APlusPlusEngine::GetWindowWidth(),
		-1 * (float)APlusPlusEngine::GetWindowWidth(),
		 1 * (float)APlusPlusEngine::GetWindowHeight(), 
		-1 * (float)APlusPlusEngine::GetWindowHeight(),
		1.0f, 1000.0f);
	orthoCamera->setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(0, 0, 50.0f));
	orthoCamera->updateCamera();  // Again, if we change anythign about the camera, we need to call update again

	defaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	currCamera = defaultCamera;
}

CameraManager::~CameraManager()
{
//	DebugMsg::out("Deleted CameraManager\n");
	delete defaultCamera;
	delete orthoCamera;
}

Camera* CameraManager::Get()
{
	return currCamera;
}

Camera* CameraManager::Get2D()
{
	return orthoCamera;
}
void CameraManager::Load(Camera* c)
{
	currCamera = c;
}