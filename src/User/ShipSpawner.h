#ifndef _ShipSpawner
#define _ShipSpawner

#include "GameObject.h"

class Bomb;

class ShipSpawner : public GameObject
{
public:
	ShipSpawner(const int& x, const int& z, const int& r, const float& t);
	~ShipSpawner();

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

	ShipSpawner();

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Alarm0();
	virtual void Alarm1();


};

#endif