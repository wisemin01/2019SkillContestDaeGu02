#include "DXUT.h"
#include "PlayerControllerStage1.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "Fade.h"
#include "TextRenderer.h"
#include "EnemyController.h"

void PlayerControllerStage1::Enter()
{
	m_bIsStart = false;
	m_bIsWarningTimeAttack = false;
	m_bIsWarningTimeEnd = false;

	Base->SetCameraRange(2000, 2000);

	CreateObjects();
	CreateStage1UI();
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
}

void PlayerControllerStage1::Exit()
{
	SoundSource::Find("FTu1L")->Stop();
}

void PlayerControllerStage1::Start()
{
	Base->m_pTimeAttackTimer = Timer::Create(300.0f);

	SoundSource::Find("FTu1L")->Play(true);

	Base->Say(L"사령관님!");
	Base->Say(L"현재 서면 길거리가 적에게\n점령당할 위기입니다.");
	Base->Say(L"5분 내로 모든 적들을 물리치고\n상황이 심각한 부산역으로\n가야합니다.");
	Base->Say(L"서둘러주세요.");

	SoundSource::Load("button-3", L"Sound/button-3.wav")->DuplicatePlay();
	m_pMissionPanelText->SetContext(L"빠르게 모든 적들을 물리치고\n부산역으로 향하자.");

	m_pBlackFadePanel->renderer->CurrentAnime->AnimeColor = Color::White;
	m_pBlackFadePanel->AddComponent<Fade<Color>>()->Set(Color(0, 0, 0, 0), FadeTarget::Renderer_Alpha, -0.35f);
}

void PlayerControllerStage1::CreateStage1UI()
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

void PlayerControllerStage1::InputHelp()
{
	if (Input::GetKeyDown(KeyCode::H))
	{
		Base->Say(L"[!] 조작법\n* 마우스 좌클릭 - 범위 선택\n* 마우스 우클릭 - 선택된 객체 이동, 공격\n* 마우스 이동 - 카메라 이동");
	}
}

void PlayerControllerStage1::TimeUpdate()
{
	float anyTime = Base->m_pTimeAttackTimer->AnyTime;

	if (m_bIsWarningTimeAttack == false && anyTime <= 60.0f)
	{
		SoundSource::Load("beep-warning", L"Sound/beep-warning.wav")->Play();

		m_bIsWarningTimeAttack = true;
		Base->Say(L"시간이 얼마 남지 않았어요!\n서둘러주세요.");
		m_pTimePanelText->SetColor(Color::Red);
	}

	if (m_bIsWarningTimeEnd == false && anyTime <= 0.0f)
	{
		m_bIsWarningTimeEnd = true;
		Base->Say(L"시간이 다 되었어요.....\n임무 실패입니다.....");
		m_pTimePanelText->SetColor(Color::Black);
	}

	m_pTimePanelText->SetContext(SecondsToTimeStringW(anyTime));
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
		pBackground->transform->Position = Vector3(1000, 562.5, 0);
	}

	// ================================================================
	// OBSTACLE OBJECTS
	// ================================================================

	{
		Actor* pParasol = ACTOR.Create(TagType::Obstacle, 3);
		pParasol->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("pasasol")));
		pParasol->renderer->Change(UnitStateType::Idle);
		pParasol->transform->Position = Vector3(800, 300, 0);
		pParasol->AddComponent<Collider>()->SetRange(100, 100);
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
