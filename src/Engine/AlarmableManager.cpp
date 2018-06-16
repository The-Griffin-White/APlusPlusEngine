#include "AlarmableManager.h"

#include "AlarmableAttorneyToAlarmableManager.h"

#include "APPECore.h"
#include "TimeManager.h"

AlarmableManager::~AlarmableManager()
{
	// We should delete the objects somewhere else, so just clear the list
	priorityQueue.clear();
	DebugMsg::out("DrawableManager deleted\n");
}

AlarmableManager::TimelineRef AlarmableManager::Register(Alarmable* up, ALARM_ID id, float t)
{
	return priorityQueue.insert({ t, {up, id} });
}

void AlarmableManager::ProcessElements()
{
	auto itr = priorityQueue.begin();
	float frameTime = TimeManager::GetTimeInSeconds();

	while (itr != priorityQueue.end())
	{
		if (frameTime >= (*itr).first)
		{
			ALARM_ID id = (*itr).second.second;
			Alarmable* al = (*itr).second.first;
			++itr;
			AlarmableAttorneyToAlarmableManager::TriggerAlarm(al, id);
		}
		else
		{
			break;
		}
	}
}

void AlarmableManager::Deregister(TimelineRef itr)
{
	priorityQueue.erase(itr);
}