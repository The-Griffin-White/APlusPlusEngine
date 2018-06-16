#ifndef _Tank
#define _Tank

#include "GameObject.h"

class EnemyShip;
class EnemyBomb;
class Sprite;

class Tank : public GameObject
{
public:
	Tank();
	void Initialize();
	void Initialize(const Vect& inPos);
	~Tank();

	void ChangeUpVector(Vect up);

	virtual void Collision(EnemyShip* p);
	virtual void Collision(EnemyBomb* p);
	virtual void Collision();

	const Vect& GetPos() const;

	void SetRespawnAlarm();

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();

	virtual void KeyPressed(APPE_KEY k);

	const int MaxHealth = 5;
	int currHealth;

	int lightNum;

	Sprite* xhair;
	float xhairScale;
	GraphicsObject_TextureLight *pGObj_t99Body;
	GraphicsObject_TextureLight *pGObj_t99Turret;

	Vect FirstPersonOffset;
	Vect FirstPersonLookAt;
	Vect ThirdPersonOffset;
	Vect ThirdPersonLookAt;

	Vect* camOffset;
	Vect* camLookAt;

	Matrix scale;
	Matrix rot;
	float tankRotAngle;
	Vect pos;
	float tankSpeed;

	Matrix turretRot;
	Vect turretPos;
	float turretRotAngle;

	bool bCanFire;

	const int maxUp = 80;
	const int maxDown = -50;

	int degrees;
};

#endif Tank