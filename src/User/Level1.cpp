#include "APPECore.h"
#include "Level1.h"

#include "PlayerManager.h"
#include "Plane.h"

#include "Bomb.h"
#include "EnemyTank.h"
#include "EnemyBomb.h"
#include "EnemyShip.h"
#include "Tank.h"

#include "TankSpawner.h"
#include "ShipSpawner.h"
#include "EnemyTankFactory.h"
#include "EnemyShipFactory.h"
#include "EnemyBombFactory.h"
#include "BombFactory.h"

#include "SceneManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "APlusPlusEngine.h"

#include "Level2.h"

Level1::Level1()
{
	pCam3D = nullptr;
	tp = nullptr;
	sp = nullptr;
}

Level1::~Level1()
{
	delete sp;
	delete tp;
}

void Level1::Initialize()
{
	SFXManager::SetFogParameters(200, 1000, Colors::Gray);

	APlusPlusEngine::SetBackgroundColor(Colors::Blue, 1.0f);

	SkyBoxManager::Choose("sky");

	Scene::SetTerrain("tankTerrain");
	Scene::SetTerrainMaterial(Colors::Black, Colors::DarkOliveGreen, Vect(1, 1, 1));

	SetCollisionPair<Bomb, EnemyTank>();
	SetCollisionPair<Bomb, EnemyShip>();
	SetCollisionPair<Bomb, ShipSpawner>();
	SetCollisionPair<Bomb, TankSpawner>();
	SetCollisionPair<EnemyBomb, Tank>();
	SetCollisionPair<EnemyShip, Tank>();
	SetCollisionTerrain<Bomb>();
	SetCollisionTerrain<EnemyBomb>();

	PlayerManager::SpawnTank();

	tp = new TankSpawner(-500, 500, 400, 10.0f);
	sp = new ShipSpawner(500, -500, 400, 10.0f);

	pCam3D = SceneManager::GetCurrentCamera();	

	pCam3D->setPerspective(PI / 3, 
		float(APlusPlusEngine::GetWindowWidth()) / float(APlusPlusEngine::GetWindowHeight()), 
		1.0f, 10000.0f);
}

void Level1::Update()
{
	if (!tp->isActive() && !sp->isActive())
	{
		SceneManager::SetNextScene(new Level2);
	}
}

void Level1::SceneEnd()
{
	PlayerManager::RemoveTank();
	EnemyTankFactory::RecallEnemyTank();
	EnemyShipFactory::RecallEnemyShip();
	EnemyBombFactory::RecallBomb();
	BombFactory::RecallBomb();
}

void Level1::Draw()
{
}