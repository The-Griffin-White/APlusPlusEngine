#ifndef _SceneChangeNullCommand
#define _SceneChangeNullCommand

#include "SceneChangeCommandBase.h"

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	virtual void execute() {};
};

#endif