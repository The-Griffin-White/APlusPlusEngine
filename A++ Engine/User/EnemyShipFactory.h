#ifndef _EnemyShipFactory
#define _EnemyShipFactory

#include <stack>
#include <list>
#include "AzulCore.h"

class EnemyShip;

class EnemyShipFactory
{
private:
	static EnemyShipFactory *ptrInstance;

	EnemyShipFactory() {};
	EnemyShipFactory(const EnemyShipFactory&) = delete;
	EnemyShipFactory& operator=(const EnemyShipFactory&) = delete;
	~EnemyShipFactory();

	static EnemyShipFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyShipFactory;
		return *ptrInstance;
	}

	std::stack<EnemyShip*> recycledEnemyShips;
	std::list<EnemyShip*> activeEnemyShips;

	void privUpdateTarget(const Vect &inPos);

	void privCreateEnemyShip(const Vect &Pos);
	void privRecycleEnemyShip(EnemyShip* b);
	void privRecallEnemyShip();
	void privDelete();

public:
	static void UpdateTarget(const Vect &inPos) { Instance().privUpdateTarget(inPos); };

	static void CreateEnemyShip(const Vect &Pos) { Instance().privCreateEnemyShip(Pos); };
	static void RecycleEnemyShip(EnemyShip* b) { Instance().privRecycleEnemyShip(b); };
	static void RecallEnemyShip() { Instance().privRecallEnemyShip(); };

	static void Delete() { Instance().privDelete(); };
	static void Terminate();


};

#endif