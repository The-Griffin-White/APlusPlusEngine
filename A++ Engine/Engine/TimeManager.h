#ifndef _TimeManager
#define _TimeManager

class FreezeTime;

class TimeManager
{
private:
	static TimeManager *ptrInstance;

	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager();

	static TimeManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TimeManager;
		return *ptrInstance;
	}

	FreezeTime* frzTime;

	float privGetTimeInSeconds();
	float privGetFrameTime();
	void privUpdateTime(float t);

	float previousTime;
	float currentTime;
	float frameTime;

public:
	/// \brief Returns the time in seconds since the beginning of the game.
	/// \ingroup TIME-MANAGE
	///
	///\ par Actual function is dealt with in the private singleton function
	static float GetTimeInSeconds() { return Instance().privGetTimeInSeconds(); };
	/// \brief Returns the time in seconds since the last frame.
	/// \ingroup TIME-MANAGE
	///
	/// \par Actual function is dealt with in the private singleton function
	static float GetFrameTime() { return Instance().privGetFrameTime(); };
	/// \brief Update The current time in this manager.
	/// \ingroup TIME-MANAGE
	///
	/// \param t The time passed in to use as our current time
	/// \par Actual function is dealt with in the private singleton function
	static void UpdateTime(float t) { Instance().privUpdateTime(t); };

};

#endif