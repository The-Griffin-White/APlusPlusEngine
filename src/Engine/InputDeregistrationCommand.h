#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "Inputable.h"

class InputDeregistrationCommand : public SceneRegistrationCommand
{
private:
	Inputable* ptrIn;
	APPE_KEY key;
	Inputable::INPUT_EVENT_TYPE type;
	Inputable::KeyMgrRef keyMgrRef;
	Inputable::RegMapRef inputableRef;

public:
	InputDeregistrationCommand(
		Inputable* p, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e,
		Inputable::KeyMgrRef mgrRef, Inputable::RegMapRef inRef
	);

	virtual void execute();


};

#endif