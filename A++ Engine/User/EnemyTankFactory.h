#ifndef _EnemyTankFactory
#define _EnemyTankFactory

#include <stack>
#include <list>
#include "AzulCore.h"

class EnemyTank;

class EnemyTankFactory
{
private:
	static EnemyTankFactory *ptrInstance;

	EnemyTankFactory() {};
	EnemyTankFactory(const EnemyTankFactory&) = delete;
	EnemyTankFactory& operator=(const EnemyTankFactory&) = delete;
	~EnemyTankFactory();

	static EnemyTankFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyTankFactory;
		return *ptrInstance;
	}

	bool privAllTanksDead();

	std::stack<EnemyTank*> recycledEnemyTanks;
	std::list<EnemyTank*> activeEnemyTanks;

	void privUpdateTarget(const Vect &inPos);

	void privCreateEnemyTank(const Vect &Pos);
	void privRecycleEnemyTank(EnemyTank* b);
	void privRecallEnemyTank();
	void privDelete();

public:
	static void UpdateTarget(const Vect &inPos) { Instance().privUpdateTarget(inPos); };
	static bool AllTanksDead() { return Instance().privAllTanksDead(); };

	static void CreateEnemyTank(const Vect &Pos) { Instance().privCreateEnemyTank(Pos); };
	static void RecycleEnemyTank(EnemyTank* b) { Instance().privRecycleEnemyTank(b); };
	static void RecallEnemyTank() { Instance().privRecallEnemyTank(); };

	static void Delete() { Instance().privDelete(); };
	static void Terminate();


};

#endif