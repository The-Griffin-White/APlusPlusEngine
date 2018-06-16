#include "Keyboard.h"
#include "Engine.h"

bool Keyboard::IsKeyActive(APPE_KEY key)
{
	return ( GetKeyState(key) & 0x08000);
}