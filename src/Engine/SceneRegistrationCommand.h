#ifndef _SceneRegistrationCommand
#define _SceneRegistrationCommand

#include "CommandBase.h"

class SceneRegistrationCommand : public CommandBase
{
public:
	virtual void execute() {};
	virtual ~SceneRegistrationCommand() {};
};

#endif