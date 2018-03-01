#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public SceneRegistrationCommand
{
private:
	Alarmable* ptrAl;
	AlarmableManager::ALARM_ID al_id;

public:
	AlarmDeregistrationCommand(Alarmable* p, AlarmableManager::ALARM_ID id);

	virtual void execute();
};

#endif