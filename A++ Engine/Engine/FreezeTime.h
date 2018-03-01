// FreezeTime
// Andre Berthiaume, Jan 2016

#ifndef _FreezeTime
#define _FreezeTime

#include "AzulCore.h"

class FreezeTime
{
private:
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F10;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F9;

	float totalFrozenTime;
	bool freeze_mode_active;

	/// \brief Waits for key to be pressed to stop, start, or single-frame time
	/// \ingroup TIME-MANAGE
	float WaitAndReturnFrozenTime(float activetime);
	/// \brief Inefficient but simple function to wait for a key to be released
	/// \ingroup TIME-MANAGE
	bool HackedKeyRelease(AZUL_KEY k);

public:
	FreezeTime();
	~FreezeTime(){};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	/// \brief Used to get the time in seconds from game start minus the frozen time
	/// \ingroup TIME-MANAGE
	///
	/// \param sys_time Current time passed in by TimeManager
	/// \par This is also where we freeze time if the appropriate key is pressed
	float GetTimeInSeconds(float sys_time);
};

#endif _FreezeTime