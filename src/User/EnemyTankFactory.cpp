#include "EnemyTankFactory.h"
#include "EnemyTank.h"

EnemyTankFactory* EnemyTankFactory::ptrInstance = nullptr;

EnemyTankFactory::~EnemyTankFactory()
{
	DebugMsg::out("Deleting BombFactory\n");
	// forcefully delete all recycled gameobjects
	this->privDelete();
}

void EnemyTankFactory::privDelete()
{
	while (!recycledEnemyTanks.empty())
	{
		delete recycledEnemyTanks.top();
		recycledEnemyTanks.pop();
	}
}

bool EnemyTankFactory::privAllTanksDead()
{
	return activeEnemyTanks.empty();
}

void EnemyTankFactory::privUpdateTarget(const Vect &inPos)
{
	for (auto itr = activeEnemyTanks.begin(); itr != activeEnemyTanks.end(); ++itr)
	{
		(*itr)->InputPos(inPos);
	}
}

void EnemyTankFactory::privCreateEnemyTank(const Vect &Pos)
{
	EnemyTank* b;
	if (recycledEnemyTanks.empty())
	{
		b = new EnemyTank;
	}
	else
	{
		b = recycledEnemyTanks.top();
		recycledEnemyTanks.pop();
	}
	activeEnemyTanks.push_front(b);
	b->Initialize(Pos);
}

void EnemyTankFactory::privRecycleEnemyTank(EnemyTank* b)
{
	DebugMsg::out("Recycling a bomb\n");
	activeEnemyTanks.remove(b);
	recycledEnemyTanks.push(b);
}

void EnemyTankFactory::privRecallEnemyTank()
{
	DebugMsg::out("Recalling all bombs from scene\n");
	while (!activeEnemyTanks.empty())
	{
		activeEnemyTanks.front()->SubmitExit();
		this->privRecycleEnemyTank(activeEnemyTanks.front());
	}
}

void EnemyTankFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}