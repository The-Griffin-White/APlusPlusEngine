#ifndef _Level1
#define _Level1

#include "../Engine/Scene.h"

class Camera;
class Tank;
class Plane;

class Level1 : public Scene
{
public:
	Level1();
	~Level1();

private:
	virtual void Initialize();
	void Update();
	void Draw();

	Tank* pTank;
	Plane *pPlane;
	Camera *pCam3D;

};

#endif