#include "CameraOrthoCmd.h"
#include "CameraAttorneyToCommands.h"

void CameraOrthoCmd::execute()
{
	CameraAttorneyToCommands::SetOrthographicMatrix(pCam);
}