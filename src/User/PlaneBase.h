#ifndef _PlaneBase
#define _PlaneBase

#include "GameObject.h"

class SpaceFrigate;


class PlaneBase : public GameObject
{
public:
	static const float scale;

	PlaneBase() = delete;
	PlaneBase(Texture* tex);
	void Initialize();
	virtual ~PlaneBase();

	virtual void Collision(SpaceFrigate* sf);

private:
	virtual void Draw();
	virtual void Alarm0();
	virtual void SceneEntry();
	virtual void SceneExit();

	GraphicsObject_TextureLight *pGObj_Plane;
	const int rowNum = 14;
	const int totalNum = rowNum * rowNum;
	Matrix* mWorldArray;

};

#endif