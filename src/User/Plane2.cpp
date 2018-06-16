#include "Plane2.h"
#include "APlusPlusEngine.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

#include "MovementDemoScene.h"
#include "SecondDemoScene.h"
#include "SpaceFrigate.h"

Plane2::Plane2()
	: PlaneBase(TextureManager::Get("gravel"))
{
}