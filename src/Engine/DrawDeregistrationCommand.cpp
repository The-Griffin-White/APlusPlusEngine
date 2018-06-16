#include "DrawDeregistrationCommand.h"
#include "Drawable.h"

#include "DrawableAttorneyToDrawDeregCmd.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* p)
{
	ptrDr = p;
}

void DrawDeregistrationCommand::execute()
{
	DrawableAttorneyToDrawDeregCmd::DrawDeregistration(ptrDr);
}