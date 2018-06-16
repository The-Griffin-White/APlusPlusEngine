#ifndef _UpdateableAttorneyToUpdateDeregCmd
#define _UpdateableAttorneyToUpdateDeregCmd

#include "Updateable.h"

class UpdateableAttorneyToUpdateDeregCmd
{
private:
	friend class UpdateDeregistrationCommand;
	static void UpdateDeregistration(Updateable* al)
	{
		al->SceneDeregistration();
	};
};

#endif