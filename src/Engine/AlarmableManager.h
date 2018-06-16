#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>

class Alarmable;

class AlarmableManager
{
public:
	enum ALARM_ID { ALARM_0 = 0, ALARM_1 = 1, ALARM_2 = 2 };
	static const int ALARM_NUMBER = 3;

private:
	using AlarmEvent = std::pair< Alarmable*, ALARM_ID >;

public:
	using Timeline = std::multimap<float, AlarmEvent>;
	using TimelineRef = Timeline::iterator;

	AlarmableManager() {};
	~AlarmableManager();

	/// \brief Registers an alarmable to go off.
	/// \ingroup ALARM-MANAGE
	/// \param up Pointer to the Alarmable.
	/// \param id Which alarm is going off (0, 1, 2)
	/// \param t Time from now when the alarm will go off
	TimelineRef Register(Alarmable* up, ALARM_ID id, float t);
	/// \brief Goes through the list and sets off any alarms that are past their time.
	/// \ingroup ALARM-MANAGE
	void ProcessElements();
	/// \brief Deregisters an alarm.
	/// \ingroup ALARM-MANAGE
	/// \param itr Pointer to the iterator of the Alarm we are deregistering.
	void Deregister(TimelineRef itr);

private:
	Timeline priorityQueue;

};

#endif