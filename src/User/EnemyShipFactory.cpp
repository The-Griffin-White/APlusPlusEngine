#include "EnemyShipFactory.h"
#include "EnemyShip.h"

EnemyShipFactory* EnemyShipFactory::ptrInstance = nullptr;

EnemyShipFactory::~EnemyShipFactory()
{
	DebugMsg::out("Deleting BombFactory\n");
	// forcefully delete all recycled gameobjects
	this->privDelete();
}

void EnemyShipFactory::privDelete()
{
	for (auto const& i : activeEnemyShips)
	{
		delete i;
	}
	while (!recycledEnemyShips.empty())
	{
		delete recycledEnemyShips.top();
		recycledEnemyShips.pop();
	}
}

void EnemyShipFactory::privUpdateTarget(const Vect &inPos)
{
	for (auto itr = activeEnemyShips.begin(); itr != activeEnemyShips.end(); ++itr)
	{
		(*itr)->InputPos(inPos);
	}
}

void EnemyShipFactory::privCreateEnemyShip(const Vect &Pos)
{
	EnemyShip* b;
	if (recycledEnemyShips.empty())
	{
		b = new EnemyShip;
	}
	else
	{
		b = recycledEnemyShips.top();
		recycledEnemyShips.pop();
	}
	activeEnemyShips.push_front(b);
	b->Initialize(Pos);
}

void EnemyShipFactory::privRecycleEnemyShip(EnemyShip* b)
{
//	DebugMsg::out("Recycling an EnemyTank\n");
	activeEnemyShips.remove(b);
	recycledEnemyShips.push(b);
}

void EnemyShipFactory::privRecallEnemyShip()
{
	DebugMsg::out("Recalling all enemy ships from scene\n");
	while (!activeEnemyShips.empty())
	{
		activeEnemyShips.front()->SubmitExit();
		recycledEnemyShips.push(activeEnemyShips.front());
		activeEnemyShips.pop_front();
	}
}

void EnemyShipFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}