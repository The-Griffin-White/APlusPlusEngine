#ifndef _Axis
#define _Axis

#include "../Engine/GameObject.h"

class Axis : public GameObject
{
public:
	Axis();
	void Initialize();
	~Axis();

private:
	virtual void Draw();
	virtual void SceneEntry();
	virtual void SceneExit();
	GraphicsObject_ColorNoTexture *pGObj_Axis;

};

#endif