#ifndef _SpriteRegistrationCommand
#define _SpriteRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "Sprite.h"

class SpriteRegistrationCommand : public SceneRegistrationCommand
{
private:
	Sprite* ptrSp;

public:
	SpriteRegistrationCommand(Sprite* p);

	virtual void execute();


};

#endif