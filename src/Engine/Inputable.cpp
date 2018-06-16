#include "Inputable.h"

#include "KeyboardEventManager.h"
#include "SceneManager.h"
#include "SceneAttorneyToInputable.h"

#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"

Inputable::Inputable()
{
}

Inputable::~Inputable()
{
	DebugMsg::out("Inputable deleted\n");
	auto itr = regMap.begin();
	while (itr != regMap.end())
	{
		delete itr->second.regCmd;
		delete itr->second.deregCmd;
		itr++;
	}
	regMap.clear();
}

void Inputable::SceneRegistration(RegMapRef ref, APPE_KEY k, INPUT_EVENT_TYPE e)
{
	// We are NOT currently registered
	if (!ref->second.registered)
	{
		ref->second.registered = true;
		KeyMgrRef keyMgrRef = SceneAttorneyToInputable::Register(this, k, e);
		ref->second.deregCmd = new InputDeregistrationCommand(this, k, e, keyMgrRef, ref);
	}
}

void Inputable::SceneDeregistration(RegMapRef ref, KeyMgrRef keyRef, APPE_KEY k, INPUT_EVENT_TYPE e)
{
	// We ARE currently registered
	if (ref->second.registered)
	{
		ref->second.registered = false;
		SceneAttorneyToInputable::Deregister(keyRef, k, e);
	}
}

void Inputable::SubmitKeyRegistration(APPE_KEY k, INPUT_EVENT_TYPE e)
{
	InputRegistrationCommand* tmp;
	auto itr = regMap.find({ k, e });
	if (itr != regMap.end())
	{ 
		tmp = itr->second.regCmd;
	}
	else
	{
		itr = regMap.insert({ { k, e }, {nullptr, nullptr, false} }).first;
		tmp = new InputRegistrationCommand(this, k, e, itr);
		itr->second.regCmd = tmp;
	}
	SceneAttorneyToInputable::SubmitCommand(tmp);
}

void Inputable::SubmitKeyDeregistration(APPE_KEY k, INPUT_EVENT_TYPE e)
{
	auto itr = regMap.find({ k, e });
	SceneAttorneyToInputable::SubmitCommand(itr->second.deregCmd);
}