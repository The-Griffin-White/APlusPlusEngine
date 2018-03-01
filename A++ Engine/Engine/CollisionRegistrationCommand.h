#ifndef _CollisionRegistrationCommand
#define _CollisionRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "CollidableGroup.h"

template <typename C>
class CollisionRegistrationCommand : public SceneRegistrationCommand
{
private:
	C* ptrC;

public:
	CollisionRegistrationCommand(C* c) : ptrC(c) {};
	void execute() { CollidableGroup<C>::Register(ptrC); };

};

#endif