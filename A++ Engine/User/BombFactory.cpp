#include "BombFactory.h"
#include "Bomb.h"

BombFactory* BombFactory::ptrInstance = nullptr;

BombFactory::~BombFactory()
{
	DebugMsg::out("Deleting BombFactory\n");
	// forcefully delete all recycled gameobjects
	while (!recycledBombs.empty())
	{
		delete recycledBombs.top();
		recycledBombs.pop();
	}
}

void BombFactory::privCreateBomb(const Vect &Pos, const Matrix& Rot)
{
	Bomb* b;
	if (recycledBombs.empty())
	{
		b = new Bomb;
	}
	else
	{
		b = recycledBombs.top();
		recycledBombs.pop();
	}
	b->Initialize(Pos, Rot);
}

void BombFactory::privRecycleBomb(Bomb* b)
{
	DebugMsg::out("Recycling a bomb\n");
	activeBombs.remove(b);
	recycledBombs.push(b);
}

void BombFactory::privRecallBomb()
{
	DebugMsg::out("Recalling all bombs from scene\n");
	while (!activeBombs.empty())
	{
		recycledBombs.push(activeBombs.front());
		activeBombs.pop_front();
	}
}

void BombFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}