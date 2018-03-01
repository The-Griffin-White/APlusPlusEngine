#include "UpdateRegistrationCommand.h"
#include "Updateable.h"

#include "UpdateableAttorneyToUpdateRegCmd.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updateable* p)
{
	ptrUp = p;
}

void UpdateRegistrationCommand::execute()
{
	UpdateableAttorneyToUpdateRegCmd::UpdateRegistration(ptrUp);
}