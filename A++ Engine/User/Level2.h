#ifndef _Level2
#define _Level2

#include "../Engine/Scene.h"

class Camera;
class Tank;
class Plane2;

class Level2 : public Scene
{
public:
	Level2();
	~Level2();

private:
	virtual void Initialize();
	void Update();
	void Draw();

	Tank* pTank;
	Plane2 *pPlane;
	Camera *pCam3D;

};

#endif