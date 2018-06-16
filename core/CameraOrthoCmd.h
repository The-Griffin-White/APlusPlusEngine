#ifndef _CameraOrthoCmd
#define _CameraOrthoCmd

#include "CameraProjCmd.h"

class CameraOrthoCmd : public CameraProjCmd
{
public:
	CameraOrthoCmd(Camera* cam) : CameraProjCmd(cam) {};
	virtual void execute() override;

};

#endif