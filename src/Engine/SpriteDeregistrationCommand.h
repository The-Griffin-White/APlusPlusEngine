#ifndef _SpriteDeregistrationCommand
#define _SpriteDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "Sprite.h"

class SpriteDeregistrationCommand : public SceneRegistrationCommand
{
private:
	Sprite * ptrSp;

public:
	SpriteDeregistrationCommand(Sprite* p);

	virtual void execute();


};

#endif