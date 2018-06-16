#ifndef _Explosion
#define _Explosion

#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion();
	void Initialize(const Vect& p);
	~Explosion();

private:
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();

	virtual void Alarm0();

	GraphicsObject_ColorNoTexture *Explode;

	float scale;
	Vect pos;

};

#endif