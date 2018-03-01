#ifndef _SceneChangeNextCommand
#define _SceneChangeNextCommand

#include "SceneChangeCommandBase.h"

class Scene;

class SceneChangeNextCommand : public SceneChangeCommandBase
{
public:
	SceneChangeNextCommand();
	void SetScenePtr(Scene* s);
	~SceneChangeNextCommand();
	virtual void execute();

private:
	Scene* ptrSc;

};

#endif