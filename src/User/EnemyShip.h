#ifndef _EnemyShip
#define _EnemyShip

#include "GameObject.h"

#include "Tank.h"

class SpaceFrigate;
class Bomb;

class EnemyShip : public GameObject
{
public:
	EnemyShip();
	void Initialize();
	void Initialize(const Vect& inPos);
	~EnemyShip();

	void ChangeUpVector(Vect up);

	virtual void Collision(Bomb* p);
	virtual void Collision(Tank* p);
	virtual void Collision();

	void InputPos(const Vect& inPos);

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();

	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;
	Vect BSphereColor;

	float speed;

	Matrix ShipScale;
	Matrix ShipRot;
	Vect ShipPos;
	Vect lookAt;
};

#endif