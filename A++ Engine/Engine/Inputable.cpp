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
	auto itr1 = regCmdMap.begin();
	while (!regCmdMap.empty())
	{
		delete itr1->second;
		regCmdMap.erase(itr1++);
	}
	auto itr2 = deregCmdMap.begin();
	while (!deregCmdMap.empty())
	{
		delete itr2->second;
		deregCmdMap.erase(itr2++);
	}
}

void Inputable::SceneRegistration(AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	auto itr = currentlyRegistered.find({ k, e });
	// We are NOT currently registered
	if (itr != currentlyRegistered.end())
	{
		if (!itr->second)
		{
			itr->second = true;
			SceneAttorneyToInputable::Register(this, k, e);
		}
	}
	else
	{
		currentlyRegistered.insert({ {k, e}, true });
		SceneAttorneyToInputable::Register(this, k, e);
	}
}

void Inputable::SceneDeregistration(AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	auto itr = currentlyRegistered.find({ k, e });
	// We ARE currently registered
	if (itr != currentlyRegistered.end())
	{
		if (itr->second)
		{
			itr->second = false;
			SceneAttorneyToInputable::Deregister(this, k, e);
		}
	}
}

void Inputable::SubmitKeyRegistration(AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	InputRegistrationCommand* tmp;
	auto itr = regCmdMap.find({ k, e });
	if (itr != regCmdMap.end())
	{ 
		tmp = itr->second;
	}
	else
	{
		tmp = new InputRegistrationCommand(this, k, e);
		regCmdMap.insert({ { k, e }, tmp });
	}
	SceneAttorneyToInputable::SubmitCommand(tmp);
}

void Inputable::SubmitKeyDeregistration(AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	InputDeregistrationCommand* tmp;
	auto itr = deregCmdMap.find({ k, e });
	if (itr != deregCmdMap.end())
	{
		tmp = itr->second;
	}
	else
	{
		tmp = new InputDeregistrationCommand(this, k, e);
		deregCmdMap.insert({ { k, e }, tmp });
	}
	SceneAttorneyToInputable::SubmitCommand(tmp);
}