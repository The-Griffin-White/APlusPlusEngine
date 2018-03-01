#ifndef _GodCam
#define _GodCam

#include "../Engine/GameObject.h"

class GodCam : public GameObject
{
public:
	GodCam();
	~GodCam();
	virtual void Initialize();

	virtual void Update();

	virtual void SceneEntry();
	virtual void SceneExit();

	void RegisterKeys();
	void DeregisterKeys();

	virtual void KeyPressed(AZUL_KEY k);

private:
	bool registered;
	float rotspeed;
	float camspeed;

};

#endif