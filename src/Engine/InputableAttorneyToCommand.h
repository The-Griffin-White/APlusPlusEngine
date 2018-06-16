#ifndef _InputableAttorneyToCommand
#define _InputableAttorneyToCommand

#include "Inputable.h"

class InputableAttorneyToCommand
{
	friend class InputRegistrationCommand;
	friend class InputDeregistrationCommand;

	static void SceneRegistration(Inputable* p, Inputable::RegMapRef ref, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e)
	{ p->SceneRegistration(ref, k, e); };
	static void SceneDeregistration(Inputable* p, Inputable::RegMapRef ref, Inputable::KeyMgrRef keyRef, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e)
	{ p->SceneDeregistration(ref, keyRef, k, e); };
};

#endif