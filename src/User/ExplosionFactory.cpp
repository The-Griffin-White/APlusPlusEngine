#include "ExplosionFactory.h"
#include "Explosion.h"

ExplosionFactory* ExplosionFactory::ptrInstance = nullptr;

ExplosionFactory::~ExplosionFactory()
{
	DebugMsg::out("Deleting ExplosionFactory\n");
	this->privDelete();
}

void ExplosionFactory::privDelete()
{
	for (auto const& i : activeExpl)
	{
		delete i;
	}
	while (!recycledExpl.empty())
	{
		delete recycledExpl.top();
		recycledExpl.pop();
	}
}

void ExplosionFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void ExplosionFactory::privCreateExplosion(const Vect &Pos)
{
	Explosion* b;
	if (recycledExpl.empty())
	{
		b = new Explosion;
	}
	else
	{
		b = recycledExpl.top();
		recycledExpl.pop();
	}
	activeExpl.push_front(b);
	b->Initialize(Pos);
}
void ExplosionFactory::privRecycleExplosion(Explosion* b)
{
	activeExpl.remove(b);
	recycledExpl.push(b);
}
void ExplosionFactory::privRecallExplosion()
{
	DebugMsg::out("Recalling all explosions from scene\n");
	while (!activeExpl.empty())
	{
		activeExpl.front()->SubmitExit();
		recycledExpl.push(activeExpl.front());
		activeExpl.pop_front();
	}
}