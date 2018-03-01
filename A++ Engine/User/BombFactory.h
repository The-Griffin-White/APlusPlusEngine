#ifndef _BombFactory
#define _BombFactory

#include <stack>
#include <list>
#include "AzulCore.h"

class Bomb;

class BombFactory
{
private:
	static BombFactory *ptrInstance;

	BombFactory() {};
	BombFactory(const BombFactory&) = delete;
	BombFactory& operator=(const BombFactory&) = delete;
	~BombFactory();

	static BombFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BombFactory;
		return *ptrInstance;
	}
	
	std::stack<Bomb*> recycledBombs;
	std::list<Bomb*> activeBombs;

	void privCreateBomb(const Vect &Pos, const Matrix& Rot);
	void privRecycleBomb(Bomb* b);
	void privRecallBomb();

public:
	static void CreateBomb(const Vect &Pos, const Matrix& Rot) { Instance().privCreateBomb(Pos, Rot); };
	static void RecycleBomb(Bomb* b) { Instance().privRecycleBomb(b); };
	static void RecallBomb() { Instance().privRecallBomb(); };

	static void Terminate();


};

#endif _BombFactory