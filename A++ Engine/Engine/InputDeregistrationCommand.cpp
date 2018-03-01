#include "InputDeregistrationCommand.h"

#include "Inputable.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* p, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e)
	: ptrIn(p), key(k), type(e)
{
}

void InputDeregistrationCommand::execute()
{
	ptrIn->SceneDeregistration(key, type);
}