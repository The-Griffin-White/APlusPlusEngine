#ifndef _SpaceFrigate
#define _SpaceFrigate

#include "GameObject.h"

class Plane;
class TestShip;

class SpaceFrigate : public GameObject
{
public:
	SpaceFrigate();
	void Initialize();
	~SpaceFrigate();

	void ChangeUpVector(Vect up);

	virtual void Collision(Plane* p);
	virtual void Collision(TestShip* p);
	virtual void Collision();

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	void RegisterKeys();
	void DeregisterKeys();

	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();
	virtual void Alarm2();

	virtual void KeyPressed(APPE_KEY k);
	virtual void KeyReleased(APPE_KEY k);

	float SpaceFrigate::ShipTransSpeed = 2.0f;
	float SpaceFrigate::ShipRotAng = .05f;

	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;

	Vect CamShipOffset;
	Vect CamLookAt;

	Matrix ShipScale;
	Matrix ShipRot;
	Vect ShipPos;
	bool newCell;

	bool canFire;
	bool registered;
};

#endif