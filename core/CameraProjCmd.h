#ifndef _CameraProjCmd
#define _CameraProjCmd

#include "Camera.h"

class CameraProjCmd
{
public:
	CameraProjCmd(Camera* cam) : pCam(cam) {};
	virtual void execute() = 0;

protected:
	Camera * pCam;

};

#endif