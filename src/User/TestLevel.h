#ifndef _TestLevel
#define _TestLevel

#include "Scene.h"

class Camera;
class GodCam;
class SpaceFrigate;
class TestShip;
class Plane;
class Sprite;

class TestLevel : public Scene
{
public:
	TestLevel();
	~TestLevel();

private:
	virtual void Initialize();
	virtual void SceneEnd();
	void Update();
	void Draw();

	Camera *pCam3D;
	GodCam *pGodCam;
	SpaceFrigate *pPlayer;
	TestShip *pTestShip;
	TestShip *pTestShip2;
	Plane* pPlane;

	Sprite* pSprite;
};

#endif