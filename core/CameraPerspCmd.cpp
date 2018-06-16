#include "CameraPerspCmd.h"
#include "CameraAttorneyToCommands.h"

void CameraPerspCmd::execute()
{
	CameraAttorneyToCommands::SetPerspectiveMatrix(pCam);
}