#ifndef _CameraPerspCmd
#define _CameraPerspCmd

#include "CameraProjCmd.h"

class CameraPerspCmd : public CameraProjCmd
{
public:
	CameraPerspCmd(Camera* cam) : CameraProjCmd(cam) {};
	virtual void execute() override;

};

#endif