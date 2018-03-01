#include "EnemyBombFactory.h"
#include "EnemyBomb.h"

EnemyBombFactory* EnemyBombFactory::ptrInstance = nullptr;

EnemyBombFactory::~EnemyBombFactory()
{
	DebugMsg::out("Deleting BombFactory\n");
	// forcefully delete all recycled gameobjects
	while (!recycledBombs.empty())
	{
		delete recycledBombs.top();
		recycledBombs.pop();
	}
}

void EnemyBombFactory::privCreateBomb(const Vect &Pos, const Matrix& Rot)
{
	EnemyBomb* b;
	if (recycledBombs.empty())
	{
		b = new EnemyBomb;
	}
	else
	{
		b = recycledBombs.top();
		recycledBombs.pop();
	}
	b->Initialize(Pos, Rot);
}

void EnemyBombFactory::privRecycleBomb(EnemyBomb* b)
{
	DebugMsg::out("Recycling a bomb\n");
	activeBombs.remove(b);
	recycledBombs.push(b);
}

void EnemyBombFactory::privRecallBomb()
{
	DebugMsg::out("Recalling all bombs from scene\n");
	while (!activeBombs.empty())
	{
		recycledBombs.push(activeBombs.front());
		activeBombs.pop_front();
	}
}

void EnemyBombFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}