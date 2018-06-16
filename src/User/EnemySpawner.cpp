#include "EnemySpawner.h"
#include "EnemyTankFactory.h"
#include "EnemyShipFactory.h"

EnemySpawner::EnemySpawner(const int& x, const int& z, const int& r, const float& t)
	: xpos(x), zpos(z), range(r), time(t)
{
	int randx = rand() % xpos + range;
	int randz = rand() % zpos + range;
	EnemyTankFactory::CreateEnemyTank(Vect((float)randx, 1, (float)randz));
	randx = rand() % xpos + range;
	randz = rand() % zpos + range;
	EnemyShipFactory::CreateEnemyShip(Vect((float)randx, 10, (float)randz));

	SubmitEntry();
}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::SceneEntry()
{
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}

void EnemySpawner::SceneExit()
{
	Alarmable::DeregisterAll();
}

void EnemySpawner::Alarm0()
{
	if (rand() % 3 == 1)
	{
		int randx = rand() % xpos + range;
		int randz = rand() % zpos + range;
		EnemyTankFactory::CreateEnemyTank(Vect((float)randx, 1, (float)randz));
	}
	else
	{
		int randx = rand() % xpos + range;
		int randz = rand() % zpos + range;
		EnemyShipFactory::CreateEnemyShip(Vect((float)randx, 10, (float)randz));
	}
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_1, 0.01f);
}

void EnemySpawner::Alarm1()
{
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}