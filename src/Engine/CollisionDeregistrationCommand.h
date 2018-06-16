#ifndef _CollisionDeregistrationCommand
#define _CollisionDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "CollidableGroup.h"

template <typename C>
class CollisionDeregistrationCommand : public SceneRegistrationCommand
{
private:
	C * ptrC;

public:
	CollisionDeregistrationCommand(C* c) : ptrC(c) {};
	void execute() { CollidableGroup<C>::Deregister(ptrC); };

};

#endif