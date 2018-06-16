#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "SceneRegistrationCommand.h"

class Updateable;

class UpdateRegistrationCommand : public SceneRegistrationCommand
{
private:
	Updateable* ptrUp;
public:
	UpdateRegistrationCommand(Updateable* p);

	virtual void execute();
};

#endif