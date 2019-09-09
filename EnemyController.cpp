#include "DXUT.h"
#include "EnemyController.h"

#include "Enemy.h"
#include "HPModule.h"

Enemy* EnemyController::SpawnEnemy(Vector3 position, int soldierType)
{
	if (soldierType == SoldierType::Ship)
	{
		Actor* pShip = ACTOR.Create(TagType::Enemy, 3);

		Enemy* pEnemy = pShip->AddComponent<Enemy>();

		pEnemy->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("stage1-enemy-ship")));
		pEnemy->renderer->AddAnimation(UnitStateType::Move, new Animation(Sprite::Find("stage1-enemy-ship")));
		pEnemy->renderer->AddAnimation(UnitStateType::Attack, new Animation(Sprite::Find("stage1-enemy-ship")));

		pEnemy->Set(100.0f, 0.1f, 120.0f, 100.0f, 10, Vector3(161, -52, 0));
		pEnemy->collider->SetRange(254, 186);

		pEnemy->transform->Position = position;
		pEnemy->GetComponent<HPModule>()->Set(100);

		return pEnemy;
	}
}
