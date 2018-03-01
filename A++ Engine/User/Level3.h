#ifndef _Level3
#define _Level3

#include "../Engine/Scene.h"

class Camera;
class Tank;
class Plane3;

class Level3 : public Scene
{
public:
	Level3();
	~Level3();

private:
	virtual void Initialize();
	void Update();
	void Draw();

	Tank* pTank;
	Plane3 *pPlane;
	Camera *pCam3D;

};

#endif