#include "Updateable.h"
#include "SceneManager.h"

#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

#include "RegistrationState.h"
#include <assert.h>
#include "APPECore.h"

#include "SceneAttorneyToUpdateable.h"

Updateable::Updateable()
{
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegistrationCmd = new UpdateRegistrationCommand(this);
	pDeregistrationCmd = new UpdateDeregistrationCommand(this);
}

Updateable::~Updateable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
	DebugMsg::out("Updateable deleted\n");
}

void Updateable::SubmitUpdateRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorneyToUpdateable::SubmitCommand(pRegistrationCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Updateable::SubmitUpdateDeregistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorneyToUpdateable::SubmitCommand(pDeregistrationCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Updateable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	storageRef = SceneAttorneyToUpdateable::Register(this);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Updateable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorneyToUpdateable::Deregister(storageRef);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}