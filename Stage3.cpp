#include "DXUT.h"
#include "Stage3.h"
#include "TextRenderer.h"

#include "FSM.h"
#include "PlayerController.h"
#include "PlayerControllerStage2.h"

void Stage3::Initialize()
{
	// ================================================================
	// PLAYER CONTROLLER
	// ================================================================

	{
		Actor* pPlayerController = ACTOR.Create(TagType::Controller, false);
		pPlayerController->AddComponent<PlayerController>();

		pPlayerController->GetComponent<FSM<PlayerController>>()->AddState(PlayerControllerType::Stage3, new PlayerControllerStage2());
		pPlayerController->GetComponent<FSM<PlayerController>>()->ChangeState(PlayerControllerType::Stage3);
	}
}
