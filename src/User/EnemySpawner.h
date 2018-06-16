#ifndef _EnemySpawner
#define _EnemySpawner

#include "GameObject.h"

class EnemySpawner : public GameObject
{
public:
	EnemySpawner(const int& x, const int& z, const int& r, const float& t);
	~EnemySpawner();

private:
	int xpos;
	int zpos;
	int range;
	float time;

	EnemySpawner();

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Alarm0();
	virtual void Alarm1();
	

};

#endif