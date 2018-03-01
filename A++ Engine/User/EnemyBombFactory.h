#ifndef _EnemyBombFactory
#define _EnemyBombFactory

#include <stack>
#include <list>
#include "AzulCore.h"

class EnemyBomb;

class EnemyBombFactory
{
private:
	static EnemyBombFactory *ptrInstance;

	EnemyBombFactory() {};
	EnemyBombFactory(const EnemyBombFactory&) = delete;
	EnemyBombFactory& operator=(const EnemyBombFactory&) = delete;
	~EnemyBombFactory();

	static EnemyBombFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyBombFactory;
		return *ptrInstance;
	}

	std::stack<EnemyBomb*> recycledBombs;
	std::list<EnemyBomb*> activeBombs;

	void privCreateBomb(const Vect &Pos, const Matrix& Rot);
	void privRecycleBomb(EnemyBomb* b);
	void privRecallBomb();

public:
	static void CreateBomb(const Vect &Pos, const Matrix& Rot) { Instance().privCreateBomb(Pos, Rot); };
	static void RecycleBomb(EnemyBomb* b) { Instance().privRecycleBomb(b); };
	static void RecallBomb() { Instance().privRecallBomb(); };

	static void Terminate();


};

#endif _EnemyBombFactory