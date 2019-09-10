#include "DXUT.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "HPModule.h"

#include "BulletAttack.h"
#include "FireAttack.h"

Enemy* EnemyController::SpawnEnemy(Vector3 position, int soldierType)
{
	if (soldierType == SoldierType::Ship)
	{
		Actor* pActor = ACTOR.Create(TagType::Enemy, 3);

		Enemy* pEnemy = pActor->AddComponent<Enemy>();

		pEnemy->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("stage1-enemy-ship")));
		pEnemy->renderer->AddAnimation(UnitStateType::Move, new Animation(Sprite::Find("stage1-enemy-ship")));
		pEnemy->renderer->AddAnimation(UnitStateType::Attack, new Animation(Sprite::Find("stage1-enemy-ship")));

		pEnemy->Set(100.0f, 0.18f, 120.0f, 100.0f, 10, Vector3(161, -52, 0));
		pEnemy->collider->SetRange(254, 186);

		pEnemy->transform->Position = position;
		pEnemy->GetComponent<HPModule>()->Set(100);
		pEnemy->SetAttackType(new BulletAttack());

		pEnemy->CreateMoveRadar(1000, 1000);
		pEnemy->CreateAttackRadar(750, 750);
		pEnemy->SetShakePowerOnDeath(25.0f);

		return pEnemy;
	}

	if (soldierType == SoldierType::Short)
	{
		Actor* pActor = ACTOR.Create(TagType::Enemy, 3);

		Enemy* pEnemy = pActor->AddComponent<Enemy>();

		pEnemy->renderer->AddAnimation(UnitStateType::Idle,
			new Animation(Sprite::Find("stage1-short-enemy"), FrameRange(0, 3), 0.3f));
		pEnemy->renderer->AddAnimation(UnitStateType::Move,
			new Animation(Sprite::Find("stage1-short-enemy"), FrameRange(4, 7), 0.3f));
		pEnemy->renderer->AddAnimation(UnitStateType::Attack,
			new Animation(Sprite::Find("stage1-short-enemy"), FrameRange(8, 11), 0.3f));

		pEnemy->Set(110.0f, 0.5f, 40.0f, 80.0f, 3, Vector3(0, 0, 0));
		pEnemy->collider->SetRange(90, 90);

		pEnemy->transform->Position = position;
		pEnemy->GetComponent<HPModule>()->Set(15);
		pEnemy->SetAttackType(new FireAttack());

		pEnemy->CreateMoveRadar(790, 790);
		pEnemy->CreateAttackRadar(250, 250);
		pEnemy->SetShakePowerOnDeath(5.0f);

		return pEnemy;
	}

	if (soldierType == SoldierType::Long)
	{
		Actor* pActor = ACTOR.Create(TagType::Enemy, 3);

		Enemy* pEnemy = pActor->AddComponent<Enemy>();

		pEnemy->renderer->AddAnimation(UnitStateType::Idle,
			new Animation(Sprite::Find("stage1-long-enemy"), FrameRange(0, 3), 0.3f));
		pEnemy->renderer->AddAnimation(UnitStateType::Move,
			new Animation(Sprite::Find("stage1-long-enemy"), FrameRange(4, 7), 0.3f));
		pEnemy->renderer->AddAnimation(UnitStateType::Attack,
			new Animation(Sprite::Find("stage1-long-enemy"), FrameRange(8, 11), 0.3f));

		pEnemy->Set(110.0f, 0.6f, 90.0f, 80.0f, 1, Vector3(0, 0, 0));
		pEnemy->collider->SetRange(95, 90);

		pEnemy->transform->Position = position;
		pEnemy->GetComponent<HPModule>()->Set(10);
		pEnemy->SetAttackType(new BulletAttack());

		pEnemy->CreateMoveRadar(900, 900);
		pEnemy->CreateAttackRadar(750, 750);
		pEnemy->SetShakePowerOnDeath(7.5f);

		return pEnemy;
	}
}
