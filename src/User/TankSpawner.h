#ifndef _TankSpawner
#define _TankSpawner

#include "GameObject.h"

class Bomb;

class TankSpawner : public GameObject
{
public:
	TankSpawner(const int& x, const int& z, const int& r, const float& t);
	~TankSpawner();

	void Collision(Bomb*);

	void Draw() override;

	bool isActive() { return active; };

private:
	GraphicsObject_TextureLight * pGObj;

	bool active;

	static const int MAX_HEALTH = 5;
	int health;

	int xpos;
	int zpos;
	int range;
	float time;

	TankSpawner();

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Alarm0();
	virtual void Alarm1();


};

#endif