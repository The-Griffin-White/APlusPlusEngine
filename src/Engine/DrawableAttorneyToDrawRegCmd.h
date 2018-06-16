#ifndef _DrawableAttorneyToDrawRegCmd
#define _DrawableAttorneyToDrawRegCmd

#include "Drawable.h"

class DrawableAttorneyToDrawRegCmd
{
private:
	friend class DrawRegistrationCommand;
	static void DrawRegistration(Drawable* al)
	{
		al->SceneRegistration();
	};
};

#endif