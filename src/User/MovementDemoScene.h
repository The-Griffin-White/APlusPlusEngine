#ifndef _MovementDemoScene
#define _MovementDemoScene

#include "Scene.h"

class Game;

class GraphicsObject_ColorNoTexture;
class GraphicsObject_TextureFlat;
class Camera;

class Tank;
class SpaceFrigate;
class Axis;
class Plane;
class GodCam;
class EnemyShip;
class EnemyTank;

class MovementDemoScene : public Scene
{
public:
	MovementDemoScene();
	~MovementDemoScene();

private:
	virtual void Initialize();
	void Update();
	void Draw();

	GodCam* pGodCam;
	Tank* tank;
	EnemyTank* enemytank;
	SpaceFrigate *spaceship;
	Axis *axis;
	Plane *plane;
	Camera *pCam3D;
	EnemyShip *testShip;

};

#endif