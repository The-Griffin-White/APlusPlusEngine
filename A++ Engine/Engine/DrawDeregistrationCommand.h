#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class DrawDeregistrationCommand : public SceneRegistrationCommand
{
private:
	Drawable* ptrDr;
public:
	DrawDeregistrationCommand(Drawable* p);

	virtual void execute();
};

#endif