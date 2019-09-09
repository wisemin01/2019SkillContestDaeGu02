#include "DXUT.h"
#include "EnemyController.h"

#include "Enemy.h"

Enemy* EnemyController::SpawnEnemy(Vector3 position, int soldierType)
{
	if (soldierType == SoldierType::Ship)
	{
		Actor* pShip = ACTOR.Create(TagType::Enemy, 3);

		Enemy* pEnemy = pShip->AddComponent<Enemy>();

		pEnemy->transform->Position = position;

		return pEnemy;
	}
}
