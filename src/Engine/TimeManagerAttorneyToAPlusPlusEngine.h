#ifndef _TimeManagerAttorneyToAPlusPlusEngine
#define _TimeManagerAttorneyToAPlusPlusEngine

#include "TimeManager.h"

class TimeManagerAttorneyToAPlusPlusEngine
{
private:
	friend class APlusPlusEngine;

	static void UpdateTime(float t) { TimeManager::UpdateTime(t); };
	static void Terminate() { TimeManager::Terminate(); };
};

#endif