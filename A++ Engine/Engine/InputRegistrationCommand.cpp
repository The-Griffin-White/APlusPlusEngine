#include "InputRegistrationCommand.h"

#include "Inputable.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* p, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
	: ptrIn(p), key(k), type(e)
{
}

void InputRegistrationCommand::execute()
{
	ptrIn->SceneRegistration(key, type);
}