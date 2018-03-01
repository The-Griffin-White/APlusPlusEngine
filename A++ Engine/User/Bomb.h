#ifndef _Bomb
#define _Bomb

#include "../Engine/GameObject.h"

class EnemyShip;
class EnemyTank;

class Bomb : public GameObject
{
public:
	Bomb();
	void Initialize(const Vect& Pos, const Matrix& Rot);
	~Bomb();

	virtual void Collision(EnemyShip* p);
	virtual void Collision(EnemyTank* p);
	virtual void Collision();

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	
	GraphicsObject_TextureLight *pGObj_Bomb;
	float fallSpeed;

	Matrix scale;
	Matrix rot;
	Vect pos;

};

#endif