#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "Inputable.h"

class InputRegistrationCommand : public SceneRegistrationCommand
{
private:
	Inputable* ptrIn;
	AZUL_KEY key;
	Inputable::INPUT_EVENT_TYPE type;

public:
	InputRegistrationCommand(Inputable* p, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e);

	virtual void execute();


};

#endif