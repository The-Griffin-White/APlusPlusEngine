#ifndef _ExplosionFactory
#define _ExplosionFactory

#include <list>
#include <stack>
#include "APPEcore.h"

class Explosion;

class ExplosionFactory
{
private:
	static ExplosionFactory *ptrInstance;

	ExplosionFactory() {};
	ExplosionFactory(const ExplosionFactory&) = delete;
	ExplosionFactory& operator=(const ExplosionFactory&) = delete;
	~ExplosionFactory();

	static ExplosionFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ExplosionFactory;
		return *ptrInstance;
	}

	std::list<Explosion*> activeExpl;
	std::stack<Explosion*> recycledExpl;

	void privCreateExplosion(const Vect &Pos);
	void privRecycleExplosion(Explosion* b);
	void privRecallExplosion();
	void privDelete();
	
public:
	static void CreateExplosion(const Vect &Pos) { Instance().privCreateExplosion(Pos); };
	static void RecycleExplosion(Explosion* b) { Instance().privRecycleExplosion(b); };
	static void RecallExplosion() { Instance().privRecallExplosion(); };

	static void Delete() { Instance().privDelete(); };
	static void Terminate();

};

#endif