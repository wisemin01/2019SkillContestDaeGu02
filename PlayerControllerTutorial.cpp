#include "DXUT.h"
#include "PlayerControllerTutorial.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "TextRenderer.h"
#include "Fade.h"
#include "Camera.h"
#include "Wobble.h"
#include "EnemyController.h"

OperatorUnit* PlayerControllerTutorial::GetOperator()
{
	Actor* pBase = ACTOR.FindActor(TagType::Operator);

	if (pBase == nullptr)
		return nullptr;

	return pBase->GetComponent<OperatorUnit>();
}

void PlayerControllerTutorial::Enter()
{
	m_bIsStartTutorial		= false;
	m_bIsQuest_Select		= false;
	m_bIsQuest_Move			= true;
	m_bIsEndListenTutorial	= false;
	m_bIsWarningTimeAttack	= false;
	m_bIsWarningTimeEnd		= false;
	m_bIsDisplayQuest[0]	= false;
	m_bIsDisplayQuest[1]	= false;
	m_bIsDisplayQuest[2]	= false;
	m_bIsDisplayQuest[3]	= false;

	OnSelect = CreateListener(RECT, OnSelectCommand);
	Base->OnSelect += OnSelect;

	OnMove = CreateListener(Vector3, OnMoveCommand);
	Base->OnRightClick += OnMove;

	CreateObjects();
	CreateTutorialUI();
}

void PlayerControllerTutorial::Stay()
{
	if (m_bIsStartTutorial == false)
	{
		Start();
		return;
	}

	if (Input::GetKeyDown(KeyCode::Space))
	{
		Camera::MainCamera()->SetShakePower(30.0f);
		Camera::MainCamera()->Shake(0.5f);
	}

	OnAttackCommand();
	CheckDisplayQuest();
	CheckEndTutorial();
	CheckFailedTutorial();
	TimeUpdate();
}

void PlayerControllerTutorial::Exit()
{
	SoundSource::Find("midnight-ride-01a")->Stop();

	Base->OnSelect.Remove(OnSelect);
	Base->OnRightClick.Remove(OnMove);

	OnSelect = nullptr;
	OnMove = nullptr;
}

void PlayerControllerTutorial::CreateTutorialUI()
{
	Actor* pTimePanelBase = ACTOR.Create(TagType::UI);

	pTimePanelBase->AddComponent<TextRenderer>()->Set("메이플스토리 Bold", 30, L"");
	pTimePanelBase->transform->Position = Vector3(288, 532, 0);

	m_pTimePanelText = pTimePanelBase->GetComponent<TextRenderer>();

	Actor* pMissionPanelBase = ACTOR.Create(TagType::UI);

	pMissionPanelBase->AddComponent<TextRenderer>()->Set("메이플스토리 Bold", 20, L"");
	pMissionPanelBase->transform->Position = Vector3(60, 192, 0);

	m_pMissionPanelText = pMissionPanelBase->GetComponent<TextRenderer>();

	m_pBlackFadePanel = ACTOR.Create(TagType::UI);

	m_pBlackFadePanel->renderer->RenderType = RenderType::UI;
	m_pBlackFadePanel->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Black")));
	m_pBlackFadePanel->renderer->Change(UnitStateType::Idle);

	m_pBlackFadePanel->transform->Position = Window::Center;
}

void PlayerControllerTutorial::Start()
{
	Base->m_pTimeAttackTimer = Timer::Create(300.0f);

	SoundSource::Find("midnight-ride-01a")->Play(true);

	m_pMissionPanelText->SetContext(L"현재 미션이 없습니다.");

	Base->Say(L"안녕하세요 사령관님!");
	Base->Say(L"저는 오퍼레이터를 맡은\n○○이라고 합니다.");
	Base->Say(L"지금부터 사령관님께\n조작법을 알려드리려고 합니다.");
	Base->Say(L"잘 따라와주세요.");
	Base->Say(L"일단 마우스 좌클릭으로\n범위를 지정해 유닛을\n선택해보세요.");

	m_bIsDisplayQuest[0] = true;

	m_bIsStartTutorial = true;

	m_pBlackFadePanel->renderer->CurrentAnime->AnimeColor = Color::White;
	m_pBlackFadePanel->AddComponent<Fade<Color>>()->Set(Color(0, 0, 0, 0), FadeTarget::Renderer_Alpha, -0.35f);
}

void PlayerControllerTutorial::OnSelectCommand(RECT rc)
{
	if (m_bIsQuest_Select == false)
	{
		auto pOperator = GetOperator();

		if (pOperator->HasWork() == false)
		{
			m_bIsQuest_Select = true;
			m_bIsQuest_Move = false;

			Say_Tutorial_Text01();
		}
	}
}

void PlayerControllerTutorial::OnMoveCommand(Vector3 v)
{
	if (m_bIsQuest_Move == false)
	{
		auto pOperator = GetOperator();

		if (pOperator->HasWork() == false)
		{
			m_bIsQuest_Move = true;
			m_bIsQuest_Attack = false;

			Say_Tutorial_Text02();
		}
	}
}

void PlayerControllerTutorial::OnAttackCommand()
{
	if (m_bIsQuest_Attack == false)
	{
		if (PlayerController::GetPlayerUnitCount() == 0)
		{
			auto pOperator = GetOperator();

			if (pOperator->HasWork() == false)
			{
				m_bIsQuest_Attack = true;
				m_bIsQuest_Anchor = false;

				Say_Tutorial_Text03(false);
			}
		}

		if (EnemyController::GetEnemyUnitCount() == 0)
		{
			auto pOperator = GetOperator();

			if (pOperator->HasWork() == false)
			{
				m_bIsQuest_Attack = true;
				m_bIsQuest_Anchor = false;

				Say_Tutorial_Text03(true);
			}
		}
	}
}

void PlayerControllerTutorial::OnAnchorCommand(Collider* other)
{
	if (other->Tag != TagType::Player)
		return;

	if (m_bIsQuest_Anchor == false)
	{
		auto pOperator = GetOperator();

		if (pOperator->HasWork() == false)
		{
			m_bIsQuest_Anchor = true;
			m_bIsEndListenTutorial = true;

			RegisterQuest(L"현재 미션이 없습니다.");
		}
	}
}

void PlayerControllerTutorial::CheckEndTutorial()
{
	if (m_bIsEndListenTutorial == false)
		return;

	auto pOperator = GetOperator();

	if (m_bIsBlackFadeEnd == false && 
		pOperator->HasWork() == false)
	{
		m_pBlackFadePanel->GetComponent<Fade<Color>>()->Set(Color(1, 1, 1, 1), FadeTarget::Renderer_Alpha, 0.45f);
		m_bIsBlackFadeEnd = true;
	}

	if (m_pBlackFadePanel->renderer->CurrentAnime->GetAlpha() >= 1.0f)
	{
		PlayerController::g_bIsEndListenTutorial = true;
		SCENE.Change("STAGE1");
	}
}

void PlayerControllerTutorial::CheckFailedTutorial()
{
	if (m_bIsTutorialFailed == false)
		return;

	auto pOperator = GetOperator();

	if (m_bIsBlackFadeEnd == false &&
		pOperator->HasWork() == false)
	{
		m_pBlackFadePanel->GetComponent<Fade<Color>>()->Set(Color(1, 1, 1, 1), FadeTarget::Renderer_Alpha, 0.45f);
		m_bIsBlackFadeEnd = true;
	}

	if (m_pBlackFadePanel->renderer->CurrentAnime->GetAlpha() >= 1.0f)
	{
		PlayerController::g_bIsEndListenTutorial = false;
		SCENE.Change("STAGE1");
	}
}

void PlayerControllerTutorial::CheckDisplayQuest()
{
	if (m_bIsDisplayQuest[0] == true)
	{
		if(RegisterQuest(L"마우스 좌클릭(드래그)을 이용해서\n유닛을 선택하자."))
		{
			m_bIsDisplayQuest[0] = false;
		}
	}

	if (m_bIsDisplayQuest[1] == true)
	{
		if(RegisterQuest(L"마우스 우클릭을 이용해서\n유닛을 이동시키자.")){
			m_bIsDisplayQuest[1] = false;
		}
	}

	if (m_bIsDisplayQuest[2] == true)
	{
		if(RegisterQuest(L"유닛을 이동시켜서\n적 함선을 모두 파괴하자."))
		{
			m_bIsDisplayQuest[2] = false;
		}
	}

	if (m_bIsDisplayQuest[3] == true)
	{
		if (RegisterQuest(L"함선들을 오른쪽으로 이동시켜서\n해운대에 정박시키자."))
		{
			m_bIsDisplayQuest[3] = false;
		}
	}
}

void PlayerControllerTutorial::TimeUpdate()
{
	float anyTime = m_pFSM->Owner->m_pTimeAttackTimer->AnyTime;

	if (m_bIsWarningTimeAttack == false && anyTime <= 60.0f)
	{
		SoundSource::Load("beep-warning", L"Sound/beep-warning.wav")->Play();

		m_bIsWarningTimeAttack = true;
		m_pFSM->Owner->Say(L"시간이 얼마 남지 않았어요!\n서둘러주세요.");
		m_pTimePanelText->SetColor(Color::Red);
	}

	if (m_bIsWarningTimeEnd == false && anyTime <= 0.0f)
	{
		m_bIsWarningTimeEnd = true;
		m_pFSM->Owner->Say(L"시간이 다 되었어요.....\n임무 실패입니다.....");
		m_pTimePanelText->SetColor(Color::Black);
		m_bIsTutorialFailed = true;
	}

	m_pTimePanelText->SetContext(SecondsToTimeStringW(anyTime));
}

bool PlayerControllerTutorial::RegisterQuest(const wstring& context)
{
	auto pOperator = GetOperator();

	if (pOperator->HasWork() == false)
	{
		SoundSource::Load("button-3", L"Sound/button-3.wav")->Play();

		m_pMissionPanelText->SetContext(context);

		return true;
	}
	
	return false;
}

void PlayerControllerTutorial::CreateObjects()
{
	// ================================================================
	// BACKGROUND OBJECTS
	// ================================================================

	{
		Actor* pBackgroundWater = ACTOR.Create(TagType::Background, 0);
		pBackgroundWater->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Background")->Get(0)));
		pBackgroundWater->renderer->Change(UnitStateType::Idle);
		pBackgroundWater->transform->Position = Vector3(1000, 562.5, 0);

		// Caust position setting
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Actor* pCaust = ACTOR.Create(TagType::Background, 1);
				pCaust->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Caust"), 0.1f));
				pCaust->renderer->Change(UnitStateType::Idle);
				pCaust->renderer->CurrentAnime->AnimeColor = Color(0, 0, 0.7f, 0.1f);
				pCaust->transform->Position = Vector3(0, 0, 0) + Vector3(384 * i, 384 * j, 0);
				pCaust->transform->Scaling(6);
			}
		}

		Actor* pBackgroundDot = ACTOR.Create(TagType::Background, 2);
		pBackgroundDot->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Background")->Get(1)));
		pBackgroundDot->renderer->Change(UnitStateType::Idle);
		pBackgroundDot->transform->Position = Vector3(1000, 562.5, 0);
		pBackgroundDot->AddComponent<Wobble>()->Set(WobbleType::Width, 3, 5);
	}

	// ================================================================
	// OBSTACLE OBJECTS
	// ================================================================

	{
		Actor* pStone01 = ACTOR.Create(TagType::Obstacle, 3);
		pStone01->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(0)));
		pStone01->renderer->Change(UnitStateType::Idle);
		pStone01->transform->Position = Vector3(1000, 158.5, 0);
		pStone01->AddComponent<Collider>()->SetRange(100, 100);

		Actor* pStone02 = ACTOR.Create(TagType::Obstacle, 3);
		pStone02->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(1)));
		pStone02->renderer->Change(UnitStateType::Idle);
		pStone02->transform->Position = Vector3(1398, 606, 0);
		pStone02->AddComponent<Collider>()->SetRange(100, 100);

		Actor* pStone03 = ACTOR.Create(TagType::Obstacle, 3);
		pStone03->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(2)));
		pStone03->renderer->Change(UnitStateType::Idle);
		pStone03->transform->Position = Vector3(259, 982, 0);
		pStone03->AddComponent<Collider>()->SetRange(100, 100);

		Actor* pStone04 = ACTOR.Create(TagType::Obstacle, 3);
		pStone04->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Stage1Stone")->Get(2)));
		pStone04->renderer->Change(UnitStateType::Idle);
		pStone04->transform->Position = Vector3(1778, 900, 0);
		pStone04->AddComponent<Collider>()->SetRange(100, 100);
	}

	// ================================================================
	// IN GAME OBJECTS ( UNITS )
	// ================================================================

	{
		PlayerController::GetMain()->SpawnSoldier(Vector3(300, 300, 0), SoldierType::Ship);
		PlayerController::GetMain()->SpawnSoldier(Vector3(450, 300, 0), SoldierType::Ship);
		PlayerController::GetMain()->SpawnSoldier(Vector3(600, 300, 0), SoldierType::Ship);

		EnemyController::GetMain()->SpawnEnemy(Vector3(1664, 424, 0), SoldierType::Ship);
		EnemyController::GetMain()->SpawnEnemy(Vector3(1664, 574, 0), SoldierType::Ship);
	}

	// ================================================================
	// UI OBJECTS
	// ================================================================

	{
		Actor* pCanvas = ACTOR.Create(TagType::UI);
		pCanvas->transform->Position = Vector3::Zero;

		Actor* pMainUI = ACTOR.Create(TagType::UI);
		pMainUI->renderer->RenderType = RenderType::UI;
		pMainUI->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("MainUI")));
		pMainUI->renderer->Change(UnitStateType::Idle);
		pMainUI->transform->Position = Window::Center;
		pMainUI->SetParent(pCanvas);

		Actor* pTextBoxPanel = ACTOR.Create(TagType::UI);
		pTextBoxPanel->renderer->RenderType = RenderType::UI;
		pTextBoxPanel->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("TextBox")));
		pTextBoxPanel->renderer->Change(UnitStateType::Idle);
		pTextBoxPanel->transform->Position = Vector3(290, 394, 0);
		pTextBoxPanel->SetParent(pCanvas);

		Actor* pTextBox = ACTOR.CreateEmpty(TagType::UI);
		auto pTextBoxComponent = pTextBox->AddComponent<TextBox>();
		pTextBox->transform->SetParent(pTextBoxPanel->transform);
		pTextBox->transform->Position = Vector3(-120, -36.5, 0);

		Actor* pOperator = ACTOR.Create(TagType::Operator);
		pOperator->AddComponent<OperatorUnit>();
		pOperator->GetComponent<OperatorUnit>()->ConnectToTextBox(pTextBoxComponent);
		pOperator->transform->Position = Vector3(70, 394, 0);
		pOperator->SetParent(pCanvas);

		Actor* pMission = ACTOR.Create(TagType::UI);
		pMission->renderer->RenderType = RenderType::UI;
		pMission->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Mission")));
		pMission->renderer->Change(UnitStateType::Idle);
		pMission->transform->Position = Vector3(168, 250, 0);
		pMission->SetParent(pCanvas);
	}
}
