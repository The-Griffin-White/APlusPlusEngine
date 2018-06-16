#ifndef _Level2
#define _Level2

#include "Scene.h"

class Camera;
class Plane2;
class TankSpawner;
class ShipSpawner;

class Level2 : public Scene
{
public:
	Level2();
	~Level2();

private:
	virtual void Initialize();
	virtual void SceneEnd();
	void Update();
	void Draw();

	Camera *pCam3D;

	TankSpawner* tp;
	ShipSpawner* sp;
	TankSpawner* tp2;
	ShipSpawner* sp2;

};

#endif