#include "Alarmable.h"
#include "SceneManager.h"
#include "SceneAttorneyToAlarmable.h"

#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"

#include "RegistrationState.h"
#include <assert.h>
#include "APPECore.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; ++i)
	{
		RegData[i].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		RegData[i].pRegistrationCmd = new AlarmRegistrationCommand(this, (AlarmableManager::ALARM_ID)i);
		RegData[i].pDeregistrationCmd = new AlarmDeregistrationCommand(this, (AlarmableManager::ALARM_ID)i);
	}
}

Alarmable::~Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; ++i)
	{
		delete RegData[i].pRegistrationCmd;
		delete RegData[i].pDeregistrationCmd;
	}
	DebugMsg::out("Alarmable deleted\n");
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	switch (id)
	{
	case AlarmableManager::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		this->Alarm2();
		break;
	}
	SceneAttorneyToAlarmable::Deregister(RegData[id].storageRef);
	RegData[id].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float t)
{
	assert(RegData[id].RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	RegData[id].pRegistrationCmd->SetAlarm(t);
	SceneAttorneyToAlarmable::SubmitCommand(RegData[id].pRegistrationCmd);
	RegData[id].RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	if (RegData[id].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		SceneAttorneyToAlarmable::SubmitCommand(RegData[id].pDeregistrationCmd);
		RegData[id].RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void Alarmable::AlarmRegistration(AlarmableManager::ALARM_ID id, float t)
{
	assert(RegData[id].RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	RegData[id].storageRef = SceneAttorneyToAlarmable::Register(this, id, t);
	RegData[id].RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::AlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorneyToAlarmable::Deregister(RegData[id].storageRef);
	RegData[id].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::DeregisterAll()
{
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; ++i)
	{
		if (RegData[i].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
		{
			SubmitAlarmDeregistration((AlarmableManager::ALARM_ID)i);
		}
	}
}