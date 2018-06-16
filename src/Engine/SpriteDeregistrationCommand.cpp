#include "SpriteDeregistrationCommand.h"
#include "SpriteAttorneyToCommands.h"

SpriteDeregistrationCommand::SpriteDeregistrationCommand(Sprite* p)
	: ptrSp(p)
{
}

void SpriteDeregistrationCommand::execute()
{
	SpriteAttorneyToCommands::SceneDeregistration(ptrSp);
}