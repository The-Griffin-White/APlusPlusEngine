#ifndef _UpdateableAttorneyToUpdateRegCmd
#define _UpdateableAttorneyToUpdateRegCmd

#include "Updateable.h"

class UpdateableAttorneyToUpdateRegCmd
{
private:
	friend class UpdateRegistrationCommand;
	static void UpdateRegistration(Updateable* al)
	{
		al->SceneRegistration();
	};
};

#endif