#ifndef _SecondDemoScene
#define _SecondDemoScene

#include "Scene.h"

class Tank;
class SpaceFrigate;
class Camera;

class SecondDemoScene : public Scene
{
public:
	SecondDemoScene() 
		: spaceship(nullptr), tank(nullptr)
	{};
	~SecondDemoScene();

private:
	virtual void Initialize();
	void Update() {};
	void Draw() {};

	SpaceFrigate *spaceship;
	Tank *tank;
	Camera *pCam3D;

};

#endif