#ifndef _Alarmable
#define _Alarmable

#include "AlarmableManager.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

enum class RegistrationState;

class Alarmable
{
public:
	Alarmable();
	virtual ~Alarmable();

protected:
	/// \brief Registers this alarm to go off in the current scene after a given time
	/// \ingroup ALARM
	///
	/// \param id Which alarm are we registering? (ALARM_0, ALARM_1, ALARM_2)
	/// \param t The time in seconds until the alarm goes off
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneEntry()
	///		{
	///			Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 10.0f);
	///		}
	/// \endcode
	void SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float t);
	/// \brief Deregisters the alarm to stop it going off
	/// \ingroup ALARM
	///
	/// \param id Which alarm are we deregistering? (ALARM_0, ALARM_1, ALARM_2)
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	///		}
	/// \endcode
	void SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);

	/// \brief Deregisters all alarms currently waiting to go off
	/// \ingroup ALARM
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Alarmable::DeregisterAll();
	///		}
	/// \endcode
	void DeregisterAll();

private:
	friend class AlarmableAttorneyToAlarmableManager;
	friend class AlarmableAttorneyToAlarmRegCmd;
	friend class AlarmableAttorneyToAlarmDeregCmd;
	/// \brief Some action defined by the user, called when ALARM_0 is registered and reaches its time
	/// \ingroup ALARM
	virtual void Alarm0() {};
	/// \brief Some action defined by the user, called when ALARM_1 is registered and reaches its time
	/// \ingroup ALARM
	virtual void Alarm1() {};
	/// \brief Some action defined by the user, called when ALARM_2 is registered and reaches its time
	/// \ingroup ALARM
	virtual void Alarm2() {};
	void TriggerAlarm(AlarmableManager::ALARM_ID id);

	void AlarmRegistration(AlarmableManager::ALARM_ID id, float t);
	void AlarmDeregistration(AlarmableManager::ALARM_ID id);

	struct RegistrationData
	{
		AlarmableManager::TimelineRef storageRef;
		RegistrationState RegStateCurr;
		AlarmRegistrationCommand* pRegistrationCmd;
		AlarmDeregistrationCommand* pDeregistrationCmd;
	};

	RegistrationData RegData[AlarmableManager::ALARM_NUMBER];


};

#endif