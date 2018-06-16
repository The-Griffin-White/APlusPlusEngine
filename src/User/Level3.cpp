#include "APPECore.h"
#include "Level3.h"

#include "PlayerManager.h"
#include "Plane3.h"

#include "Bomb.h"
#include "EnemyTank.h"
#include "EnemyBomb.h"
#include "EnemyShip.h"
#include "TankSpawner.h"
#include "ShipSpawner.h"

#include "EnemyTankFactory.h"
#include "EnemyShipFactory.h"
#include "EnemyBombFactory.h"
#include "BombFactory.h"

#include "ShaderManager.h"
#include "SceneManager.h"
#include "APlusPlusEngine.h"

Level3::Level3()
{
	pCam3D = nullptr;
	tp = nullptr;
	sp = nullptr;
	tp2 = nullptr;
	sp2 = nullptr;
}

Level3::~Level3()
{
	delete sp;
	delete sp2;
	delete tp;
	delete tp2;
}

void Level3::Initialize()
{
	SFXManager::SetFogParameters(200, 1000, Colors::Black);

	APlusPlusEngine::SetBackgroundColor(Colors::Blue, 1.0f);

	SkyBoxManager::Choose("sky");

	Scene::SetTerrain("tankTerrain3");
	Scene::SetTerrainMaterial(Colors::Black, Colors::Gray, Vect(1, 1, 1));

	SetCollisionPair<Bomb, EnemyTank>();
	SetCollisionPair<Bomb, EnemyShip>();
	SetCollisionPair<Bomb, ShipSpawner>();
	SetCollisionPair<Bomb, TankSpawner>();
	SetCollisionPair<EnemyBomb, Tank>();
	SetCollisionPair<EnemyShip, Tank>();
	SetCollisionTerrain<Bomb>();
	SetCollisionTerrain<EnemyBomb>();

	PlayerManager::SpawnTank();

	tp = new TankSpawner(100, 100, 400, 10.0f);
	sp = new ShipSpawner(300, 300, 400, 10.0f);
	tp2 = new TankSpawner(-100, 100, 400, 10.0f);
	sp2 = new ShipSpawner(-300, 300, 400, 10.0f);

	pCam3D = SceneManager::GetCurrentCamera();

	pCam3D->setPerspective(PI / 3, 
		float(APlusPlusEngine::GetWindowWidth()) / float(APlusPlusEngine::GetWindowHeight()), 
		1.0f, 10000.0f);
}

void Level3::Update()
{
}

void Level3::SceneEnd()
{
	PlayerManager::RemoveTank();
	EnemyTankFactory::RecallEnemyTank();
	EnemyShipFactory::RecallEnemyShip();
	EnemyBombFactory::RecallBomb();
	BombFactory::RecallBomb();
}

void Level3::Draw()
{
}