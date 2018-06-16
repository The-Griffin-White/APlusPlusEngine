#include "TimeManager.h"
#include "APlusPlusEngineAttorneyToTimeManager.h"

TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager::TimeManager()
	: previousTime(0), currentTime(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

float TimeManager::privGetTimeInSeconds()
{
	return currentTime;
}
float TimeManager::privGetFrameTime()
{
	return frameTime;
}
void TimeManager::privUpdateTime(float t)
{
	previousTime = currentTime;
	currentTime = t;
	frameTime = currentTime - previousTime;
	if (previousTime == 0) DebugMsg::out("frame 1 time == %f\n", frameTime);
}