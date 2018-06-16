#ifndef _CameraAttorneyToCommands
#define _CameraAttorneyToCommands

#include "Camera.h"

class CameraAttorneyToCommands
{
private:
	friend class CameraOrthoCmd;
	friend class CameraPerspCmd;
	static void SetPerspectiveMatrix(Camera* cam) { cam->privUpdatePerspective(); };
	static void SetOrthographicMatrix(Camera* cam) { cam->privUpdateOrthographic(); };
};

#endif