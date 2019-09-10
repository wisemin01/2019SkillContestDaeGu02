#include "DXUT.h"
#include "Stage2.h"
#include "TextRenderer.h"

#include "FSM.h"
#include "PlayerController.h"
#include "PlayerControllerStage2.h"

void Stage2::Initialize()
{
	// ================================================================
	// RESOURCE LOADING
	// ================================================================

	{
		Sprite::Load("stage2-background", "Stage2/background.png");
		Sprite::Load("stage2-barricade", "Stage2/barricade%d.png", 7);
		Sprite::Load("stage2-car", "Stage2/car%d.png", 2);
		Sprite::Load("stage2-building", "Stage2/building%d.png", 3);
	}

	// ================================================================
	// PLAYER CONTROLLER
	// ================================================================

	{
		Actor* pPlayerController = ACTOR.Create(TagType::Controller, false);
		pPlayerController->AddComponent<PlayerController>();

		pPlayerController->GetComponent<FSM<PlayerController>>()->AddState(PlayerControllerType::Stage2, new PlayerControllerStage2());
		pPlayerController->GetComponent<FSM<PlayerController>>()->ChangeState(PlayerControllerType::Stage2);
	}
}
