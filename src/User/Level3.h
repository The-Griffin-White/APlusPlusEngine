#ifndef _Level3
#define _Level3

#include "Scene.h"

class Camera;
class Plane3;
class TankSpawner;
class ShipSpawner;

class Level3 : public Scene
{
public:
	Level3();
	~Level3();

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