#ifndef _InputableAttorneyToSKManager
#define _InputableAttorneyToSKManager

#include "Inputable.h"

class InputableAttorneyToSKManager
{
private:
	friend class SingleKeyEventManager;
	static void KeyPressed(Inputable* p, AZUL_KEY k) { p->KeyPressed(k); }
	static void KeyReleased(Inputable* p, AZUL_KEY k) { p->KeyReleased(k); };

};

#endif