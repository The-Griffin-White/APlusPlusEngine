#ifndef _Plane3
#define _Plane3

#include "../Engine/GameObject.h"

class SpaceFrigate;

class Plane3 : public GameObject
{
public:
	Plane3();
	void Initialize();
	~Plane3();

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