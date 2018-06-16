#ifndef _TestShip
#define _TestShip

#include "GameObject.h"

class Plane;
class SpaceFrigate;

class TestShip : public GameObject
{
public:
	TestShip();
	void Initialize();
	void Initialize(const Vect& pos);
	~TestShip();

	virtual void Collision(Plane* p);
	virtual void Collision(SpaceFrigate* p);
	virtual void Collision();

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();

	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;

	Matrix world;
};

#endif