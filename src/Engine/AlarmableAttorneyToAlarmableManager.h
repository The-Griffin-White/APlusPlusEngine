#ifndef _AlarmableAttorneyToAlarmableManager
#define _AlarmableAttorneyToAlarmableManager

#include "AlarmableManager.h"
#include "Alarmable.h"

class AlarmableAttorneyToAlarmableManager
{
private:
	friend class AlarmableManager;
	static void TriggerAlarm(Alarmable* up, AlarmableManager::ALARM_ID id) { up->TriggerAlarm(id); };

};

#endif