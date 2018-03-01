#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public SceneRegistrationCommand
{
private:
	Alarmable* ptrAl;
	AlarmableManager::ALARM_ID al_id;
	float time;
public:
	AlarmRegistrationCommand(Alarmable* p, AlarmableManager::ALARM_ID id);
	void SetAlarm(float t);

	virtual void execute();
};

#endif