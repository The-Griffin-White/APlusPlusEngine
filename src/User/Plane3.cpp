#include "Plane3.h"
#include "APlusPlusEngine.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

#include "MovementDemoScene.h"
#include "SecondDemoScene.h"
#include "SpaceFrigate.h"

Plane3::Plane3()
	: PlaneBase(TextureManager::Get("rock"))
{
}