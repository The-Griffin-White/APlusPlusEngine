#include "AlarmRegistrationCommand.h"
#include "Alarmable.h"

#include "TimeManager.h"

#include "AlarmableAttorneyToAlarmRegCmd.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* p, AlarmableManager::ALARM_ID id)
	: ptrAl(p), time(0), al_id(id)
{
}

void AlarmRegistrationCommand::SetAlarm(float t)
{
	time = TimeManager::GetTimeInSeconds() + t;
}

void AlarmRegistrationCommand::execute()
{
	AlarmableAttorneyToAlarmRegCmd::AlarmDeregistration(ptrAl, al_id, time);
}