#include "AzulCore.h"
#include "Level3.h"

#include "Tank.h"
#include "Plane3.h"

#include "Bomb.h"
#include "EnemyTank.h"
#include "EnemyBomb.h"
#include "EnemyShip.h"

#include "EnemyTankFactory.h"
#include "EnemyShipFactory.h"

#include "../Engine/SceneManager.h"
#include "../Engine/APlusPlusEngine.h"

Level3::Level3()
{
	pTank = nullptr;
	pPlane = nullptr;
	pCam3D = nullptr;
}

Level3::~Level3()
{
	delete pTank;
	delete pPlane;
}

void Level3::Initialize()
{
	APlusPlusEngine::SetBackgroundColor(Colors::Maroon, 1.0f);

	pTank = new Tank;
	pTank->Initialize(Vect(0, 1, 0));

	pPlane = new Plane3;
	pPlane->Initialize();

	EnemyTankFactory::CreateEnemyTank(Vect(100, 1, 100));
	EnemyTankFactory::CreateEnemyTank(Vect(-100, 1, -100));
	EnemyTankFactory::CreateEnemyTank(Vect(-100, 1, 100));
	EnemyShipFactory::CreateEnemyShip(Vect(100, 10, -100));

	SetCollisionPair<Bomb, EnemyTank>();
	SetCollisionPair<Bomb, EnemyShip>();
	SetCollisionPair<EnemyBomb, Tank>();
	SetCollisionPair<EnemyShip, Tank>();

	pCam3D = SceneManager::GetCurrentCamera();

	pCam3D->setViewport(0, 0, APlusPlusEngine::GetWindowWidth(), APlusPlusEngine::GetWindowHeight());
	pCam3D->setPerspective(35.0f, float(APlusPlusEngine::GetWindowWidth()) / float(APlusPlusEngine::GetWindowHeight()), 1.0f, 5000.0f);
}

void Level3::Update()
{
}

void Level3::Draw()
{
}