#ifndef _Tank
#define _Tank

#include "../Engine/GameObject.h"

class EnemyShip;
class EnemyBomb;

class Tank : public GameObject
{
public:
	Tank();
	void Initialize();
	void Initialize(const Vect& inPos);
	~Tank();

	virtual void Collision(EnemyShip* p);
	virtual void Collision(EnemyBomb* p);
	virtual void Collision();

	const Vect& GetPos() const;

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();

	virtual void KeyPressed(AZUL_KEY k);

	const int MaxHealth = 100;
	int currHealth;

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
};

#endif Tank