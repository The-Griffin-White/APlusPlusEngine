#ifndef _UpdateableAttorneyToUpdateableManager
#define _UpdateableAttorneyToUpdateableManager

#include "Updateable.h"

class UpdateableAttorneyToUpdateableManager
{
private:
	friend class UpdateableManager;
	static void Update(Updateable* up) { up->Update(); };

};

#endif