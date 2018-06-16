#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Updateable;

class UpdateDeregistrationCommand : public SceneRegistrationCommand
{
private:
	Updateable* ptrUp;
public:
	UpdateDeregistrationCommand(Updateable* p);

	virtual void execute();
};

#endif