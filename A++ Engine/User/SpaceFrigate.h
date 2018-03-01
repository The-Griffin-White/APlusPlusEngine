#ifndef _SpaceFrigate
#define _SpaceFrigate

#include "../Engine/GameObject.h"

class Plane;
class EnemyShip;

class SpaceFrigate : public GameObject
{
public:
	SpaceFrigate();
	void Initialize();
	~SpaceFrigate();

	virtual void Collision(Plane* p);
	virtual void Collision(EnemyShip* p);
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

	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);

	float SpaceFrigate::ShipTransSpeed = 0.5f;
	float SpaceFrigate::ShipRotAng = .05f;
	bool BsphereToggle;

	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;

	Vect CamShipOffset;
	Vect CamLookAt;

	Matrix ShipScale;
	Matrix ShipRot;
	Vect ShipPos;

	bool canFire;
	bool registered;
};

#endif