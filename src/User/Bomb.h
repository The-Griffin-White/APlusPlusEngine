#ifndef _Bomb
#define _Bomb

#include "GameObject.h"

class EnemyShip;
class EnemyTank;
class TankSpawner;
class ShipSpawner;

class Bomb : public GameObject
{
public:
	Bomb();
	void Initialize(const Vect& Pos, const Matrix& Rot);
	~Bomb();

	virtual void Collision(EnemyShip* p);
	virtual void Collision(EnemyTank* p);
	virtual void Collision(TankSpawner* p);
	virtual void Collision(ShipSpawner* p);
	virtual void Collision();

	virtual void TerrainCollision();

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();
	
	GraphicsObject_ColorNoTexture *pGObj_Bomb;
	float fallSpeed;

	Matrix scale;
	Matrix rot;
	Vect pos;

	int lightNum;

};

#endif