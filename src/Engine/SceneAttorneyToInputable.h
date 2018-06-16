#ifndef _SceneAttorneyToInputable
#define _SceneAttorneyToInputable

#include "Inputable.h"

class SceneRegistrationCommand;

class SceneAttorneyToInputable
{
public:
	using KeyMgrRef = std::list<Inputable*>::iterator;

private:
	friend class Inputable;

	static void SubmitCommand(SceneRegistrationCommand* c);

	static KeyMgrRef Register(Inputable* in, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e);

	static void Deregister(Inputable::KeyMgrRef keyRef, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e);
};

#endif