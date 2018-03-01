#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class DrawRegistrationCommand : public SceneRegistrationCommand
{
private:
	Drawable* ptrDr;
public:
	DrawRegistrationCommand(Drawable* p);

	virtual void execute();
};

#endif