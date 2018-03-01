#include "TimeManager.h"
#include "APlusPlusEngineAttorneyToTimeManager.h"
#include "FreezeTime.h"

TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager::TimeManager()
	: previousTime(0), currentTime(0)
{
	frzTime = new FreezeTime;
}

TimeManager::~TimeManager()
{
	delete frzTime;
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
	currentTime = frzTime->GetTimeInSeconds(t);
	frameTime = currentTime - previousTime;
}