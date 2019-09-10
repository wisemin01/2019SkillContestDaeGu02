#include "DXUT.h"
#include "PlayerControllerStage1.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "Fade.h"
#include "TextRenderer.h"
#include "EnemyController.h"
#include "Trigger.h"

void PlayerControllerStage1::Enter()
{
	m_bIsStart = false;
	m_bIsWarningTimeAttack = false;
	m_bIsWarningTimeEnd = false;

	Base->SetCameraRange(2000, 2000);

	CreateObjects();
	CreateStage1UI();

	Base->transform->Position = Vector3(1000, 1500, 0);
}

void PlayerControllerStage1::Stay()
{
	if (m_bIsStart == false)
	{
		Start();

		m_bIsStart = true;
	}

	InputHelp();
	TimeUpdate();
	StatusUpdate();
}

void PlayerControllerStage1::Exit()
{
	SoundSource::Find("FTu1L")->Stop();
}

void PlayerControllerStage1::OnStageEndTrigger(Collider* other)
{
	if (other->Tag == TagType::Player)
	{
		m_pBlackFadePanel->GetComponent<Fade<Color>>()->Set(Color(1, 1, 1, 1), FadeTarget::Renderer_Alpha, 0.45f);
		m_bIsStageEnd = true;
	}
}

void PlayerControllerStage1::Start()
{
	Base->m_pTimeAttackTimer = Timer::Create(300.0f);

	SoundSource::Find("FTu1L")->Play(true);

	Base->Say(L"��ɰ���!");
	Base->Say(L"���� �ؿ�밡 �ΰ����� �κ��鿡��\n���ɴ��� �����Դϴ�.");
	Base->Say(L"5�� ���� ��� ������ ����ġ��\n��Ȳ�� �ɰ��� ���� ��Ÿ���\n���ؾ� �մϴ�.");
	Base->Say(L"���ѷ��ּ���.");

	SoundSource::Load("button-3", L"Sound/button-3.wav")->DuplicatePlay();
	m_pMissionPanelText->SetContext(L"������ ��� ������ ����ġ��\n���� ��Ÿ��� ������.");

	m_pBlackFadePanel->renderer->CurrentAnime->AnimeColor = Color::White;
	m_pBlackFadePanel->AddComponent<Fade<Color>>()->Set(Color(0, 0, 0, 0), FadeTarget::Renderer_Alpha, -0.35f);
}

void PlayerControllerStage1::CreateStage1UI()
{
	Actor* pTimePanelBase = ACTOR.Create(TagType::UI);

	pTimePanelBase->AddComponent<TextRenderer>()->Set("�����ý��丮 Bold", 30, L"");
	pTimePanelBase->transform->Position = Vector3(288, 532, 0);

	m_pTimePanelText = pTimePanelBase->GetComponent<TextRenderer>();

	Actor* pMissionPanelBase = ACTOR.Create(TagType::UI);

	pMissionPanelBase->AddComponent<TextRenderer>()->Set("�����ý��丮 Bold", 20, L"");
	pMissionPanelBase->transform->Position = Vector3(60, 192, 0);

	m_pMissionPanelText = pMissionPanelBase->GetComponent<TextRenderer>();

	m_pBlackFadePanel = ACTOR.Create(TagType::UI);

	m_pBlackFadePanel->renderer->RenderType = RenderType::UI;
	m_pBlackFadePanel->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Black")));
	m_pBlackFadePanel->renderer->Change(UnitStateType::Idle);

	m_pBlackFadePanel->transform->Position = Window::Center;
}

void PlayerControllerStage1::InputHelp()
{
	if (Input::GetKeyDown(KeyCode::H))
	{
		Base->Say(L"[!] ���۹�\n* ���콺 ��Ŭ�� - ���� ����\n* ���콺 ��Ŭ�� - ���õ� ��ü �̵�, ����\n* ���콺 �̵� - ī�޶� �̵�");
	}
}

void PlayerControllerStage1::TimeUpdate()
{
	float anyTime = Base->m_pTimeAttackTimer->AnyTime;

	if (m_bIsWarningTimeAttack == false && anyTime <= 60.0f)
	{
		SoundSource::Load("beep-warning", L"Sound/beep-warning.wav")->Play();

		m_bIsWarningTimeAttack = true;
		Base->Say(L"�ð��� �� ���� �ʾҾ��!\n���ѷ��ּ���.");
		m_pTimePanelText->SetColor(Color::Red);
	}

	if (m_bIsWarningTimeEnd == false && anyTime <= 0.0f)
	{
		m_bIsWarningTimeEnd = true;
		Base->Say(L"�ð��� �� �Ǿ����.....\n�ӹ� �����Դϴ�.....");
		m_pTimePanelText->SetColor(Color::Black);
		m_bIsQuestFail = true;
		m_bIsStageEnd = true;
	}

	m_pTimePanelText->SetContext(SecondsToTimeStringW(anyTime));
}

void PlayerControllerStage1::StatusUpdate()
{
	if (m_bIsWarning == false && PlayerController::GetPlayerUnitCount() == 5)
	{
		Base->Say(L"�Ʊ� �κ��� ���ذ� Ů�ϴ�.\n�����ϼ���!");

		m_bIsWarning = true;
	}

	if (m_bIsCheering == false && EnemyController::GetEnemyUnitCount() == 10)
	{
		Base->Say(L"���� ���� ���� 10�� ��������.\n��������!");

		m_bIsCheering = true;
	}

	if (m_bIsQuestFail == false && PlayerController::GetPlayerUnitCount() == 0)
	{
		m_pMissionPanelText->SetContext(L"���� �̼��� �����ϴ�.");

		Base->Say(L"�Ʊ��� �κ��� ��� �ı��Ǿ����...");
		Base->Say(L"��� �� �ٽ� ������ ���۵��״�\n���ݸ� �� ������ ���ּ���.");

		m_bIsQuestFail = true;
	}

	if (m_bIsQuestFail == true && GetOperator()->HasWork() == false)
	{
		m_pBlackFadePanel->GetComponent<Fade<Color>>()->Set(Color(1, 1, 1, 1), FadeTarget::Renderer_Alpha, 0.45f);
		m_bIsStageEnd = true;
	}

	if (m_bIsQuestFail == false && m_bIsQuestClear == false && EnemyController::GetEnemyUnitCount() == 0)
	{
		Base->Say(L"�ؿ���� �ٴ尡��\n���ѳ��̾��!");
		Base->Say(L"���� ���� ������ ���� ��Ÿ���\n���ѳ��� ���ø� �˴ϴ�.");

		SoundSource::Load("button-3", L"Sound/button-3.wav")->DuplicatePlay();
		m_pMissionPanelText->SetContext(L"���� ��Ÿ��� ����.\n(���� ���ʰ� ����Ǿ� �ֽ��ϴ�.)");

		Actor* pTrigger = Actor::Create(TagType::None);

		auto trigger = pTrigger->AddComponent<Trigger>();
		trigger->collider->SetRange(2000, 200);
		trigger->OnTriggerStay += CreateListener(Collider*, OnStageEndTrigger);

		pTrigger->transform->Position = Vector3(1000, 0, 0);

		m_bIsQuestClear = true;
	}

	if (m_bIsStageEnd == true && m_pBlackFadePanel->renderer->CurrentAnime->GetAlpha() >= 1.0f)
	{
		if (m_bIsQuestClear == true)
			SCENE.Change("STAGE2");
		else if (m_bIsQuestFail == true)
			SCENE.Change("STAGE1");
	}
}

void PlayerControllerStage1::CreateObjects()
{
	// ================================================================
	// BACKGROUND OBJECTS
	// ================================================================

	{
		Actor* pBackground = ACTOR.Create(TagType::Background, 0);
		pBackground->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("stage1-background-2")->Get(0)));
		pBackground->renderer->Change(UnitStateType::Idle);
		pBackground->transform->Position = Vector3(1000, 1000, 0);
	}

	// ================================================================
	// OBSTACLE OBJECTS
	// ================================================================

	{
		Actor* pParasol = ACTOR.Create(TagType::Obstacle, 3);
		pParasol->renderer->SetSingleAnimation(Sprite::Find("pasasol"));
		pParasol->transform->Position = Vector3(240, 800, 0);
		
		Actor* pBench = ACTOR.Create(TagType::Obstacle, 3);
		pBench->renderer->SetSingleAnimation(Sprite::Find("bench"));
		pBench->transform->Position = Vector3(1000, 240, 0);

		Actor* pRock = ACTOR.Create(TagType::Obstacle, 4);
		pRock->renderer->SetSingleAnimation(Sprite::Find("stage1-1-rock"));
		pRock->transform->Position = Vector3(1000, 1765.5, 0);

		Actor* pTube1 = Actor::Create(TagType::Obstacle, 3);
		pTube1->renderer->SetSingleAnimation(Sprite::Find("tube")->Get(0));
		pTube1->transform->Position = Vector3(267, 1473, 0);
		pTube1->AddComponent<Collider>()->SetRange(200, 170);

		Actor* pTube2 = Actor::Create(TagType::Obstacle, 3);
		pTube2->renderer->SetSingleAnimation(Sprite::Find("tube")->Get(1));
		pTube2->transform->Position = Vector3(1530, 942, 0);
		pTube2->AddComponent<Collider>()->SetRange(200, 170);

		Actor* pTube3 = Actor::Create(TagType::Obstacle, 3);
		pTube3->renderer->SetSingleAnimation(Sprite::Find("tube")->Get(2));
		pTube3->transform->Position = Vector3(1800, 1224, 0);
		pTube3->AddComponent<Collider>()->SetRange(200, 170);
	}

	// ================================================================
	// COLLISION OBJECTS
	// ================================================================

	{
		Actor* pBenchCol1 = Actor::Create(TagType::Obstacle, 4);
		pBenchCol1->transform->Position = Vector3(510, 285, 0);
		pBenchCol1->AddComponent<Collider>()->SetRange(340, 118);

		Actor* pBenchCol2 = Actor::Create(TagType::Obstacle, 4);
		pBenchCol2->transform->Position = Vector3(1470, 290, 0);
		pBenchCol2->AddComponent<Collider>()->SetRange(340, 118);

		Actor* pRockCol1 = Actor::Create(TagType::Obstacle, 0);
		pRockCol1->transform->Position = Vector3(120, 1880, 0);
		pRockCol1->AddComponent<Collider>()->SetRange(150, 150);

		Actor* pRockCol2 = Actor::Create(TagType::Obstacle, 0);
		pRockCol2->transform->Position = Vector3(1880, 1880, 0);
		pRockCol2->AddComponent<Collider>()->SetRange(150, 150);
	}

	// ================================================================
	// IN GAME OBJECTS ( UNITS )
	// ================================================================

	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				PlayerController::GetMain()->SpawnSoldier(Vector3(492 + 69 * i, 1447 + 102 * j, 0), SoldierType::Long);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				EnemyController::GetMain()->SpawnEnemy(Vector3(141 + 100 * i, 600 + 146 * j, 0), SoldierType::Short);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				EnemyController::GetMain()->SpawnEnemy(Vector3(841 + 100 * i, 600 + 146 * j, 0), SoldierType::Short);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			EnemyController::GetMain()->SpawnEnemy(Vector3(150 + 125 * i, 400, 0), SoldierType::Long);
		}
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
		pTextBox->transform->Position = Vector3(-110, -36.5, 0);

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

OperatorUnit* PlayerControllerStage1::GetOperator()
{
	Actor* pBase = ACTOR.FindActor(TagType::Operator);

	if (pBase == nullptr)
		return nullptr;

	return pBase->GetComponent<OperatorUnit>();
}