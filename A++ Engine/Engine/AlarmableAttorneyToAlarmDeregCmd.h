#ifndef _AlarmableAttorneyToAlarmDeregCmd
#define _AlarmableAttorneyToAlarmDeregCmd

#include "AlarmableManager.h"
#include "Alarmable.h"

class AlarmableAttorneyToAlarmDeregCmd
{
private:
	friend class AlarmDeregistrationCommand;
	static void AlarmDeregistration(Alarmable* al, AlarmableManager::ALARM_ID id)
									{ al->AlarmDeregistration(id); };
};

#endif