#include "DXUT.h"
#include "Stage1.h"
#include "Actor.h"
#include "PlayerController.h"
#include "EnemyController.h"
#include "Wobble.h"
#include "OperatorUnit.h"
#include "Soldier.h"
#include "TextBox.h"


void Stage1::Initialize()
{
	// ================================================================
	// RESOURCE LOADING
	// ================================================================

	{
		Sprite::Load("Test", "Test/test-ship(%d).png", 2);
		Sprite::Load("Test-E", "Test/enemy-test-ship(%d).png", 2);
		Sprite::Load("test-bullet", "Effect/test.png");

		Sprite::Load("Stage1Background", "Stage1/(%d).png", 2);
		Sprite::Load("Stage1Stone", "Stage1/STONE(%d).png", 4);

		Sprite::Load("Caust", "Caust/(%d).png", 32);

		Sprite::Load("MainUI", "UI/Main.png");
		Sprite::Load("TextBox", "UI/TextBox.png");
		Sprite::Load("Mission", "UI/Mission.png");
		Sprite::Load("Operator", "UI/Operator(%d).png", 3);
		Sprite::Load("select-effect", "UI/Select/%d.png", 10);
	}

	// ================================================================
	// PLAYER CONTROLLER
	// ================================================================

	{
		Actor* pPlayerController = ACTOR.Create(TagType::Controller, false);
		pPlayerController->AddComponent<PlayerController>();
	}

}