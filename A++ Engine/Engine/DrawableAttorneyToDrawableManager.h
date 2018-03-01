#ifndef _DrawableAttorneyToDrawableManager
#define _DrawableAttorneyToDrawableManager

#include "Drawable.h"

class DrawableAttorneyToDrawableManager
{
private:
	friend class DrawableManager;
	static void Draw(Drawable* dr) { dr->Draw(); };

};

#endif