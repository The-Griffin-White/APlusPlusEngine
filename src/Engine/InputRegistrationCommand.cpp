#include "InputRegistrationCommand.h"

#include "Inputable.h"
#include "InputableAttorneyToCommand.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* p, APPE_KEY k,
	Inputable::INPUT_EVENT_TYPE e, Inputable::RegMapRef inRef)
	: ptrIn(p), key(k), type(e), inputableRef(inRef)
{
}

void InputRegistrationCommand::execute()
{
	InputableAttorneyToCommand::SceneRegistration(ptrIn, inputableRef, key, type);
}