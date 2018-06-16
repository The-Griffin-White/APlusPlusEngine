#include "DrawRegistrationCommand.h"
#include "Drawable.h"

#include "DrawableAttorneyToDrawRegCmd.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* p)
{
	ptrDr = p;
}

void DrawRegistrationCommand::execute()
{
	DrawableAttorneyToDrawRegCmd::DrawRegistration(ptrDr);
}