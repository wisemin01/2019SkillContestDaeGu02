#include "DXUT.h"
#include "Stage1.h"
#include "Actor.h"
#include "PlayerController.h"
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
		Sprite::Load("Test", "Test.png");

		Sprite::Load("Stage1Background", "Stage1/(%d).png", 2);
		Sprite::Load("Stage1Stone", "Stage1/STONE(%d).png", 4);

		Sprite::Load("Caust", "Caust/(%d).png", 32);

		Sprite::Load("MainUI", "UI/Main.png");
		Sprite::Load("TextBox", "UI/TextBox.png");
		Sprite::Load("Mission", "UI/Mission.png");
		Sprite::Load("Operator", "UI/Operator(%d).png", 3);
	}

	// ================================================================
	// PLAYER CONTROLLER
	// ================================================================

	{
		Actor* pPlayerController = ACTOR.Create(TagType::Controller, false);
		pPlayerController->AddComponent<PlayerController>();
	}

	// ================================================================
	// BACKGROUND OBJECTS
	// ================================================================

	{
		Actor* pBackgroundWater = ACTOR.Create(TagType::Background);
		pBackgroundWater->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Background")->Get(0)));
		pBackgroundWater->renderer->Change(UnitStateType::Idle);
		pBackgroundWater->transform->Position = Vector3(1000, 562.5, 0);

		// Caust position setting
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Actor* pCaust = ACTOR.Create(TagType::Background);
				pCaust->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Caust"), 0.1f));
				pCaust->renderer->Change(UnitStateType::Idle);
				pCaust->renderer->CurrentAnime->AnimeColor = Color(0, 0, 0.7f, 0.1f);
				pCaust->transform->Position = Vector3(0, 0, 0) + Vector3(384 * i, 384 * j, 0);
				pCaust->transform->Scaling(6);
			}
		}

		Actor* pBackgroundDot = ACTOR.Create(TagType::Background);
		pBackgroundDot->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Background")->Get(1)));
		pBackgroundDot->renderer->Change(UnitStateType::Idle);
		pBackgroundDot->transform->Position = Vector3(1000, 562.5, 0);
		pBackgroundDot->AddComponent<Wobble>()->Set(WobbleType::Width, 3, 5);
	}

	// ================================================================
	// OBSTACLE OBJECTS
	// ================================================================

	{
		Actor* pStone01 = ACTOR.Create(TagType::Obstacle);
		pStone01->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(0)));
		pStone01->renderer->Change(UnitStateType::Idle);
		pStone01->transform->Position = Vector3(1000, 158.5, 0);
		pStone01->AddComponent<Collider>()->SetRange(100, 100);

		Actor* pStone02 = ACTOR.Create(TagType::Obstacle);
		pStone02->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(1)));
		pStone02->renderer->Change(UnitStateType::Idle);
		pStone02->transform->Position = Vector3(1398, 606, 0);
		pStone02->AddComponent<Collider>()->SetRange(100, 100);

		Actor* pStone03 = ACTOR.Create(TagType::Obstacle);
		pStone03->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(2)));
		pStone03->renderer->Change(UnitStateType::Idle);
		pStone03->transform->Position = Vector3(259, 982, 0);
		pStone03->AddComponent<Collider>()->SetRange(100, 100);

		Actor* pStone04 = ACTOR.Create(TagType::Obstacle);
		pStone04->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(2)));
		pStone04->renderer->Change(UnitStateType::Idle);
		pStone04->transform->Position = Vector3(1778, 900, 0);
		pStone04->AddComponent<Collider>()->SetRange(100, 100);
	}

	// ================================================================
	// IN GAME OBJECTS ( UNITS )
	// ================================================================

	{
		MainPlayerController->SpawnSoldier(Vector3(300, 300, 0), SoldierType::Ship);
		MainPlayerController->SpawnSoldier(Vector3(450, 300, 0), SoldierType::Ship);
	}

	// ================================================================
	// UI OBJECTS
	// ================================================================

	{
		Actor* pCanvas = ACTOR.Create(TagType::UI);
		pCanvas->transform->Position = Vector3::Zero;
		
		Actor* pMainUI = ACTOR.Create(TagType::UI);
		pMainUI->renderer->RenderType = RenderType::Rendering_UI;
		pMainUI->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("MainUI")));
		pMainUI->renderer->Change(UnitStateType::Idle);
		pMainUI->transform->Position = Window::Center;
		pMainUI->transform->SetParent(pCanvas->transform);

		Actor* pTextBoxPanel = ACTOR.Create(TagType::UI);
		pTextBoxPanel->renderer->RenderType = RenderType::Rendering_UI;
		pTextBoxPanel->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("TextBox")));
		pTextBoxPanel->renderer->Change(UnitStateType::Idle);
		pTextBoxPanel->transform->Position = Vector3(290, 394, 0);

		Actor* pTextBox = ACTOR.CreateEmpty(TagType::UI);
		auto pTextBoxComponent = pTextBox->AddComponent<TextBox>();
		pTextBox->transform->SetParent(pTextBoxPanel->transform);
		pTextBox->transform->Position = Vector3(-106, -26.5, 0);
		
		Actor* pOperator = ACTOR.Create(TagType::UI);
		pOperator->AddComponent<OperatorUnit>();
		pOperator->GetComponent<OperatorUnit>()->ConnectToTextBox(pTextBoxComponent);
		pOperator->transform->Position = Vector3(70, 394, 0);
		pOperator->transform->SetParent(pCanvas->transform);

		Actor* pMission = ACTOR.Create(TagType::UI);
		pMission->renderer->RenderType = RenderType::Rendering_UI;
		pMission->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Mission")));
		pMission->renderer->Change(UnitStateType::Idle);
		pMission->transform->Position = Vector3(168, 250, 0);
		pMission->transform->SetParent(pCanvas->transform);
	}
}

void Stage1::Update()
{
	ACTOR.Update();
	COLLISION.Update();
}

void Stage1::Render()
{
	RENDER.Render();
}

void Stage1::Release()
{
	ACTOR.Reset();
}
