#include "SpriteRegistrationCommand.h"
#include "SpriteAttorneyToCommands.h"

SpriteRegistrationCommand::SpriteRegistrationCommand(Sprite* p)
	: ptrSp(p)
{
}

void SpriteRegistrationCommand::execute()
{
	SpriteAttorneyToCommands::SceneRegistration(ptrSp);
}