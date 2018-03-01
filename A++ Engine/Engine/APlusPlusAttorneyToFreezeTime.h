#ifndef _APlusPlusAttorneyToFreezeTime
#define _APlusPlusAttorneyToFreezeTime

#include "APlusPlusEngine.h"

class APlusPlusAttorneyToFreezeTime
{
private:
	friend class FreezeTime;
	static float GetTime() { return APlusPlusEngine::GameTimeInSeconds(); };
};

#endif