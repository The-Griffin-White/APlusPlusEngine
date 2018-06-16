#ifndef _Player
#define _Player

class Tank;
class Sprite;

class Player
{
public:
	Player();
	~Player();

	void DecrementLives();
	void ResetGame();
	void SpawnTank();
	void RemoveTank();

private:
	Sprite ** lifeSprites;

	int lives;
	Tank* pTank;

};

#endif