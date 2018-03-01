#ifndef _EnemyTank
#define _EnemyTank

#include "../Engine/GameObject.h"

class Bomb;

class EnemyTank : public GameObject
{
public:
	EnemyTank();
	void Initialize();
	void Initialize(const Vect& inPos);
	~EnemyTank();

	virtual void Collision(Bomb* p);
	virtual void Collision();

	void InputPos(const Vect& inPos);

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();

	const float MaxHealth = 3;
	float currHealth;

	GraphicsObject_TextureLight *pGObj_t99Body;
	GraphicsObject_TextureLight *pGObj_t99Turret;

	Vect lookAt;

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

#endif _EnemyTank