#include "CameraManager.h"
#include "AzulCore.h"

CameraManager::CameraManager()
{
	defaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	currCamera = defaultCamera;
}

CameraManager::~CameraManager()
{
	DebugMsg::out("Deleted CameraManager\n");
	delete defaultCamera;
}

Camera* CameraManager::Get()
{
	return currCamera;
}
void CameraManager::Load(Camera* c)
{
	currCamera = c;
}