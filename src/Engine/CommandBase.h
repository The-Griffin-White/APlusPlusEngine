#ifndef _CommandBase
#define _CommandBase

#include <malloc.h>
#include "Align16.h"

class CommandBase : public Align16
{
public:
	virtual void execute() {};
	virtual ~CommandBase() {};
};

#endif