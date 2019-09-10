#pragma once
#include "DXUT.h"
#include "PlayerController.h"
#include "Soldier.h"
#include "HPModule.h"
#include "BulletAttack.h"

Soldier* PlayerController::SpawnSoldier(Vector3 position, int soldierType)
{
	if (soldierType == SoldierType::Ship)
	{
		Actor* pActor = ACTOR.Create(TagType::Player, 3);

		Soldier* pSoldier = pActor->AddComponent<Soldier>();

		pSoldier->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("stage1-player-ship")));
		pSoldier->renderer->AddAnimation(UnitStateType::Move, new Animation(Sprite::Find("stage1-player-ship")));
		pSoldier->renderer->AddAnimation(UnitStateType::Attack, new Animation(Sprite::Find("stage1-player-ship")));

		pSoldier->Set(100.0f, 0.2f, 120.0f, 100.0f, 15, Vector3(161, -52, 0));
		pSoldier->transform->Position = position;
		pSoldier->collider->SetRange(254, 186);
		pSoldier->GetComponent<HPModule>()->Set(110);
		pSoldier->SetAttackType(new BulletAttack());

		pSoldier->CreateRadar(890, 890);
		pSoldier->SetShakePowerOnDeath(25.0f);

		return pSoldier;
	}

	if (soldierType == SoldierType::Long)
	{
		Actor* pActor = ACTOR.Create(TagType::Player, 3);

		Soldier* pSoldier = pActor->AddComponent<Soldier>();

		pSoldier->renderer->AddAnimation(UnitStateType::Idle,
			new Animation(Sprite::Find("stage1-soldier"), FrameRange(0, 3), 0.3));
		pSoldier->renderer->AddAnimation(UnitStateType::Move,
			new Animation(Sprite::Find("stage1-soldier"), FrameRange(4, 7), 0.3));
		pSoldier->renderer->AddAnimation(UnitStateType::Attack,
			new Animation(Sprite::Find("stage1-soldier"), FrameRange(4, 7), 0.3));

		pSoldier->Set(140.0f, 0.4f, 100.0f, 80.0f, 3, Vector3(0, 0, 0));
		pSoldier->transform->Position = position;
		pSoldier->collider->SetRange(60, 90);
		pSoldier->GetComponent<HPModule>()->Set(10);
		pSoldier->SetAttackType(new BulletAttack());

		pSoldier->CreateRadar(800, 800);
		pSoldier->SetShakePowerOnDeath(6.0f);

		return pSoldier;
	}
}
