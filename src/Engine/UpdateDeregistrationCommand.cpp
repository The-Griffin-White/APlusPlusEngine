#include "UpdateDeregistrationCommand.h"
#include "Updateable.h"

#include "UpdateableAttorneyToUpdateDeregCmd.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updateable* p)
{
	ptrUp = p;
}

void UpdateDeregistrationCommand::execute()
{
	UpdateableAttorneyToUpdateDeregCmd::UpdateDeregistration(ptrUp);
}