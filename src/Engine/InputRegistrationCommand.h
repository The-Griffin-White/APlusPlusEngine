#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "Inputable.h"

class InputRegistrationCommand : public SceneRegistrationCommand
{
private:
	Inputable* ptrIn;
	APPE_KEY key;
	Inputable::INPUT_EVENT_TYPE type;
	Inputable::RegMapRef inputableRef;

public:
	InputRegistrationCommand(Inputable* p, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e, Inputable::RegMapRef inRef);

	virtual void execute();


};

#endif