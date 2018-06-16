#ifndef _EnemyBomb
#define _EnemyBomb

#include "../Engine/GameObject.h"

class Tank;

class EnemyBomb : public GameObject
{
public:
	EnemyBomb();
	void Initialize(const Vect& Pos, const Matrix& Rot);
	~EnemyBomb();

	virtual void Collision(Tank* p);
	virtual void Collision();

	virtual void TerrainCollision();

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();

	GraphicsObject_ColorNoTexture *pGObj_Bomb;
	float fallSpeed;

	Matrix scale;
	Matrix rot;
	Vect pos;

};

#endif