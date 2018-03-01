#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "Inputable.h"

class InputDeregistrationCommand : public SceneRegistrationCommand
{
private:
	Inputable* ptrIn;
	AZUL_KEY key;
	Inputable::INPUT_EVENT_TYPE type;

public:
	InputDeregistrationCommand(Inputable* p, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e);

	virtual void execute();


};

#endif