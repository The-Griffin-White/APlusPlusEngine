#include "AlarmDeregistrationCommand.h"
#include "Alarmable.h"

#include "AlarmableAttorneyToAlarmDeregCmd.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* p, AlarmableManager::ALARM_ID id)
	: ptrAl(p), al_id(id)
{
}

void AlarmDeregistrationCommand::execute()
{
	AlarmableAttorneyToAlarmDeregCmd::AlarmDeregistration(ptrAl, al_id);
}