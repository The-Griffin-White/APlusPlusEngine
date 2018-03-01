// This will store Camera objects and delete them when the game closes
#ifndef _CameraManager
#define _CameraManager

#include <map>			// Replace later, STL sucks

class Camera;

class CameraManager
{
public:

	CameraManager();
	~CameraManager();

	Camera* defaultCamera;
	Camera* currCamera;

	/// \brief Returns the Current camera in use.
	/// \ingroup CAM-MANAGE
	/// \return Pointer to the current Camera.
	Camera* Get();
	/// \brief Loads a new camera object into the manager, replacing the old one
	/// \ingroup CAM-MANAGE
	/// \param c New camera to be managed here, CameraManager DOES NOT handle memory for this camera
	void Load(Camera* c);
};

#endif