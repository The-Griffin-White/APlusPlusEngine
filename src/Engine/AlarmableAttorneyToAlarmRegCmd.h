#ifndef _AlarmableAttorneyToAlarmRegCmd
#define _AlarmableAttorneyToAlarmRegCmd

#include "AlarmableManager.h"
#include "Alarmable.h"

class AlarmableAttorneyToAlarmRegCmd
{
private:
	friend class AlarmRegistrationCommand;
	static void AlarmDeregistration(Alarmable* al, AlarmableManager::ALARM_ID id, float time)
									{ al->AlarmRegistration(id, time); };
};

#endif