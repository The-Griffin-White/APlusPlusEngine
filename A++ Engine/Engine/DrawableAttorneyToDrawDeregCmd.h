#ifndef _DrawableAttorneyToDrawDeregCmd
#define _DrawableAttorneyToDrawDeregCmd

#include "Drawable.h"

class DrawableAttorneyToDrawDeregCmd
{
private:
	friend class DrawDeregistrationCommand;
	static void DrawDeregistration(Drawable* al)
	{
		al->SceneDeregistration();
	};
};

#endif