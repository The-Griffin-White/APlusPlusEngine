#ifndef _APlusPlusEngineAttorneyToTimeManager
#define _APlusPlusEngineAttorneyToTimeManager

#include "APlusPlusEngine.h"

class APlusPlusEngineAttorneyToTimeManager
{
private:
	friend class TimeManager;

	static float GetTimeInSeconds() { return APlusPlusEngine::GameTimeInSeconds(); };
};

#endif