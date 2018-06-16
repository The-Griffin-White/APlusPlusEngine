#ifndef _PlayerManager
#define _PlayerManager

class Player;

class PlayerManager
{
private:
	static PlayerManager *ptrInstance;

	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;
	~PlayerManager();

	static PlayerManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PlayerManager;
		return *ptrInstance;
	}

	Player* pPlay;

public:
	static void DecrementLives();
	static void ResetGame();
	static void SpawnTank();
	static void RemoveTank();

	static void Terminate();
};

#endif