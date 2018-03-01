#ifndef _Plane2
#define _Plane2

#include "../Engine/GameObject.h"

class SpaceFrigate;

class Plane2 : public GameObject
{
public:
	Plane2();
	void Initialize();
	~Plane2();

	virtual void Collision(SpaceFrigate* sf);

private:
	virtual void Draw();
	virtual void Alarm0();
	virtual void SceneEntry();
	virtual void SceneExit();

	GraphicsObject_TextureFlat *pGObj_Plane;
	const float scale = 200.0f;
	const int rowNum = 53;
	const int totalNum = rowNum * rowNum;
	Matrix* mWorldArray;

};

#endif