#ifndef _Level1
#define _Level1

#include "Scene.h"

class Camera;
class Plane;
class GraphicsObject_Sprite;
class Sprite;
class TankSpawner;
class ShipSpawner;

class Level1 : public Scene
{
public:
	Level1();
	~Level1();

private:
	virtual void Initialize();
	virtual void SceneEnd();
	void Update();
	void Draw();

	Camera *pCam3D;

	TankSpawner* tp;
	ShipSpawner* sp;

};

#endif