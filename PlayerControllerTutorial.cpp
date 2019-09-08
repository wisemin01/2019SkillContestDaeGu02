#include "DXUT.h"
#include "PlayerControllerTutorial.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "TextRenderer.h"
#include "Fade.h"
#include "Camera.h"

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

	OnSelect = CreateListener(RECT, OnSelectCommand);
	m_pFSM->Owner->OnSelect += OnSelect;

	OnMove = CreateListener(Vector3, OnMoveCommand);
	m_pFSM->Owner->OnRightClick += OnMove;

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

	CheckDisplayQuest();
	CheckEndTutorial();
	TimeUpdate();
}

void PlayerControllerTutorial::Exit()
{
	SoundSource::Find("midnight-ride-01a")->Stop();

	m_pFSM->Owner->OnSelect.Remove(OnSelect);
	m_pFSM->Owner->OnRightClick.Remove(OnMove);

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
	m_pFSM->Owner->m_pTimeAttackTimer = Timer::Create(180.0f);

	SoundSource::Find("midnight-ride-01a")->Play(true);

	m_pMissionPanelText->SetContext(L"현재 미션이 없습니다.");

	m_pFSM->Owner->Say(L"안녕하세요 사령관님!");
	m_pFSM->Owner->Say(L"저는 오퍼레이터를 맡은\n○○이라고 합니다.");
	m_pFSM->Owner->Say(L"지금부터 사령관님께\n조작법을 알려드리려고 합니다.");
	m_pFSM->Owner->Say(L"잘 따라와주세요.");
	m_pFSM->Owner->Say(L"일단 마우스 좌클릭으로\n범위를 지정해 유닛을\n선택해보세요.");

	m_bIsDisplayQuest[0] = true;

	m_bIsStartTutorial = true;

	m_pBlackFadePanel->renderer->CurrentAnime->AnimeColor = Color::White;
	m_pBlackFadePanel->AddComponent<Fade<Color>>()->Set(Color(0, 0, 0, 0), FadeTarget::Renderer_Alpha, -0.35f);
}

void PlayerControllerTutorial::Say_Tutorial_Text01()
{
	m_pMissionPanelText->SetContext(L"현재 미션이 없습니다.");

	SoundSource::Load("mission-success", L"Sound/mission-success.wav")->Play();

	m_pFSM->Owner->Say(L"잘 하셨어요!");
	m_pFSM->Owner->Say(L"선택된 함선들은\n마우스 우클릭으로 이동시킬 수 있어요.");
	m_pFSM->Owner->Say(L"마우스 우클릭으로\n함선들을 이동시켜보세요.");

	m_bIsDisplayQuest[1] = true;
}

void PlayerControllerTutorial::Say_Tutorial_Text02()
{
	m_pMissionPanelText->SetContext(L"현재 미션이 없습니다.");

	SoundSource::Load("mission-success", L"Sound/mission-success.wav")->Play();

	m_pFSM->Owner->Say(L"잘 하셨어요!");
	m_pFSM->Owner->Say(L"설명은 여기까지에요.");
	m_pFSM->Owner->Say(L"이제부터는 실전 전투를\n참여하게 될거에요.");
	m_pFSM->Owner->Say(L"수고하셨습니다.");
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
			m_bIsEndListenTutorial = true;

			Say_Tutorial_Text02();
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
		SCENE.Change("STAGE1");
	}
}

void PlayerControllerTutorial::CheckDisplayQuest()
{
	if (m_bIsDisplayQuest[0] == true)
	{
		auto pOperator = GetOperator();

		if (pOperator->HasWork() == false)
		{
			SoundSource::Load("button-3", L"Sound/button-3.wav")->Play();

			m_pMissionPanelText->SetContext(L"마우스 좌클릭(드래그)을 이용해서\n유닛을 선택하자.");

			m_bIsDisplayQuest[0] = false;
		}
	}

	if (m_bIsDisplayQuest[1] == true)
	{
		auto pOperator = GetOperator();

		if (pOperator->HasWork() == false)
		{
			SoundSource::Load("button-3", L"Sound/button-3.wav")->Play();

			m_pMissionPanelText->SetContext(L"마우스 우클릭을 이용해서\n유닛을 이동시키자.");

			m_bIsDisplayQuest[1] = false;
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
	}

	m_pTimePanelText->SetContext(SecondsToTimeStringW(anyTime));
}
