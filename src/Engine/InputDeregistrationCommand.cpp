#include "InputDeregistrationCommand.h"

#include "Inputable.h"
#include "InputableAttorneyToCommand.h"

InputDeregistrationCommand::InputDeregistrationCommand(
	Inputable* p, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e,
	Inputable::KeyMgrRef mgrRef, Inputable::RegMapRef inRef
)
	: ptrIn(p), key(k), type(e), keyMgrRef(mgrRef), inputableRef(inRef)
{
}

void InputDeregistrationCommand::execute()
{
	InputableAttorneyToCommand::SceneDeregistration(ptrIn, inputableRef, keyMgrRef, key, type);
}