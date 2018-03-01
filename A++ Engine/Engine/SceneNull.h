#ifndef _SceneNull
#define _SceneNull

#include "../Engine/Scene.h"

class SceneNull : public Scene
{
public:
	SceneNull() {};
	~SceneNull() {};


private:
	virtual void Initialize() {};
	void Update() {};
	void Draw() {};


};

#endif