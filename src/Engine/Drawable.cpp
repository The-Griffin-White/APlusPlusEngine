#include "Drawable.h"
#include "SceneManager.h"
#include "SceneAttorneyToDrawable.h"

#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"

#include "RegistrationState.h"
#include <assert.h>
#include "APPECore.h"

Drawable::Drawable()
{
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegistrationCmd = new DrawRegistrationCommand(this);
	pDeregistrationCmd = new DrawDeregistrationCommand(this);
}

Drawable::~Drawable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
	DebugMsg::out("Drawable deleted\n");
}

void Drawable::SubmitDrawRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorneyToDrawable::SubmitCommand(pRegistrationCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorneyToDrawable::SubmitCommand(pDeregistrationCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	storageRef = SceneAttorneyToDrawable::Register(this);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorneyToDrawable::Deregister(storageRef);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}