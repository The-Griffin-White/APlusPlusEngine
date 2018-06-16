#include "APPECore.h"
#include "Level2.h"

#include "PlayerManager.h"
#include "Plane2.h"

#include "Tank.h"
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

#include "Level3.h"

Level2::Level2()
{
	pCam3D = nullptr;
	tp = nullptr;
	sp = nullptr;
	tp2 = nullptr;
	sp2 = nullptr;
}

Level2::~Level2()
{
	delete sp;
	delete sp2;
	delete tp;
	delete tp2;
}

void Level2::Initialize()
{
	SFXManager::SetFogParameters(200, 1000, Colors::DarkGray);

	APlusPlusEngine::SetBackgroundColor(Colors::Blue, 1.0f);

	SkyBoxManager::Choose("sky");

	Scene::SetTerrain("tankTerrain2");
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

void Level2::Update()
{
	if (!tp->isActive() && !sp->isActive() && !tp2->isActive() && !sp2->isActive())
	{
		SceneManager::SetNextScene(new Level3);
	}
}

void Level2::SceneEnd()
{
	PlayerManager::RemoveTank();
	EnemyTankFactory::RecallEnemyTank();
	EnemyShipFactory::RecallEnemyShip();
	EnemyBombFactory::RecallBomb();
	BombFactory::RecallBomb();
}

void Level2::Draw()
{
}