#include "TestLevel.h"

#include "APPECore.h"
#include "GodCam.h"
#include "SpaceFrigate.h"
#include "TestShip.h"
#include "Plane.h"

#include "SFXManager.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

#include "SceneManager.h"
#include "APlusPlusEngine.h"

#include "DemoScene.h"

#include "SkyBoxManager.h"

#include "SpriteFactory.h"
#include "Sprite.h"

TestLevel::TestLevel()
{
	pCam3D = nullptr;
	pGodCam = nullptr;
	pPlayer = nullptr;
	pTestShip = nullptr;
	pPlane = nullptr;
	pSprite = nullptr;
}

TestLevel::~TestLevel()
{
	delete pGodCam;
	delete pPlayer;
	delete pTestShip;
	delete pTestShip2;
	delete pPlane;
	delete pSprite;
} 

void TestLevel::Initialize()
{
	// *************************************************************************************
	// Set up all the shaders
	// *************************************************************************************

	Scene::SetTerrain("terrain2");
	Scene::SetTerrainMaterial(Colors::Black, Colors::DarkOliveGreen, Vect(1, 1, 1));

	SFXManager::ChangeDirectionalLighting(Vect(0, -.75f, 0).getNorm(),
		0.5f * Vect(1, 1, 1), 1 * Vect(1, 1, 1), 0.1f * Vect(1, 1, 1));

	DebugMsg::out("Initializing TestLevel\n");

	pCam3D = SceneManager::GetCurrentCamera();

	pCam3D->setPerspective(3.14159 / 3, float(APlusPlusEngine::GetWindowWidth()) / float(APlusPlusEngine::GetWindowHeight()), 1.0f, 10000.0f);
	pCam3D->setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(-10, 8, -8));

	SetCollisionPair<TestShip, SpaceFrigate>();
	SetCollisionTerrain<SpaceFrigate>();

	pGodCam = new GodCam;
	pGodCam->Initialize();
	pTestShip = new TestShip;
	pTestShip->Initialize();
	pTestShip2 = new TestShip;
	Vect pos;
	pos.set(60, 20, 60);
	pTestShip2->Initialize(pos);
	pPlayer = new SpaceFrigate;
	pPlayer->Initialize();
	pPlane = new Plane;
//	pPlane->Initialize();

	pSprite = SpriteFactory::CreateSprite(TextureManager::Get("Brick"), new Rect(0, 0, 100, 100));
	pSprite->Pos(200, 300);

	pSprite->SubmitRegistration();

	SkyBoxManager::Choose("sky");
}

void TestLevel::Update()
{
	if (Keyboard::IsKeyActive(APPE_KEY::KEY_0))
	{
		SceneManager::SetNextScene(new DemoScene);
	}
}

void TestLevel::Draw()
{
}

void TestLevel::SceneEnd()
{
	pSprite->SubmitDeregistration();
}