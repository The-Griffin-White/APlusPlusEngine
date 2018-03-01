#ifndef _SceneAttorneyToAlarmable
#define _SceneAttorneyToAlarmable

#include "Scene.h"
#include "SceneManager.h"

class SceneRegistrationCommand;

class SceneAttorneyToAlarmable
{
private:
	friend class Alarmable;

	static void SubmitCommand(SceneRegistrationCommand* c)
	{
		SceneManager::Get()->SubmitCommand(c);
	};

	static AlarmableManager::TimelineRef Register(Alarmable* al, AlarmableManager::ALARM_ID id, float t)
	{
		return SceneManager::Get()->RegisterAlarmable(al, id, t);
	};

	static void Deregister(AlarmableManager::TimelineRef itr)
	{
		SceneManager::Get()->DeregisterAlarmable(itr);
	};
};

#endif