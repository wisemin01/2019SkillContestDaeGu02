#include "DXUT.h"
#include "Stage1.h"
#include "Actor.h"

#include "PlayerController.h"
#include "FSM.h"
#include "PlayerControllerTutorial.h"
#include "PlayerControllerStage1.h"


void Stage1::Initialize()
{
	// ================================================================
	// RESOURCE LOADING
	// ================================================================

	{
		Sprite::Load("stage1-background-1", "Stage1/(%d).png", 2);
		Sprite::Load("stage1-background-2", "Stage1/background.png");
		Sprite::Load("bench", "Stage1/bench.png");
		Sprite::Load("pasasol", "Stage1/pasasol.png");
		Sprite::Load("stage1-1-rock", "Stage1/rock.png");
		Sprite::Load("tube", "Stage1/tube%d.png", 3);
		Sprite::Load("wave-water", "Stage1/water.png", 3);
		Sprite::Load("shadow", "Stage1/shadow%d.png", 2);
		Sprite::Load("Stage1Stone", "Stage1/STONE(%d).png", 4);

		Sprite::Load("stage1-long-enemy", "Stage1/long/(%d).png", 12);
		Sprite::Load("stage1-short-enemy", "Stage1/short/(%d).png", 12);
		Sprite::Load("stage1-soldier", "Stage1/soldier/(%d).png", 8);
		Sprite::Load("stage1-soldier-gun", "Stage1/soldier/gun.png");
		Sprite::Load("stage1-enemy-ship", "Stage1/ship/enemy.png");
		Sprite::Load("stage1-player-ship", "Stage1/ship/player.png");

		Sprite::Load("Caust", "Caust/(%d).png", 32);
	}

	// ================================================================
	// PLAYER CONTROLLER
	// ================================================================

	{
		Actor* pPlayerController = ACTOR.Create(TagType::Controller, false);
		pPlayerController->AddComponent<PlayerController>();

		if (PlayerController::IsClearTutorial())
		{
			pPlayerController->GetComponent<FSM<PlayerController>>()->AddState(PlayerControllerType::Stage1, new PlayerControllerStage1());
			pPlayerController->GetComponent<FSM<PlayerController>>()->ChangeState(PlayerControllerType::Stage1);
		}
		else
		{
			pPlayerController->GetComponent<FSM<PlayerController>>()->AddState(PlayerControllerType::Tutorial, new PlayerControllerTutorial());
			pPlayerController->GetComponent<FSM<PlayerController>>()->ChangeState(PlayerControllerType::Tutorial);
		}
	}

}