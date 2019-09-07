#include "DXUT.h"
#include "PlayerControllerStage1.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "Fade.h"
#include "TextRenderer.h"

void PlayerControllerStage1::Enter()
{
	m_bIsStart = false;
	m_bIsWarningTimeAttack = false;
	m_bIsWarningTimeEnd = false;

	CreateStage1UI();
}

void PlayerControllerStage1::Stay()
{
	if (m_bIsStart == false)
	{
		Start();

		m_bIsStart = true;
	}

	TimeUpdate();
}

void PlayerControllerStage1::Exit()
{
}

void PlayerControllerStage1::Start()
{
	m_pFSM->Owner->m_pTimeAttackTimer = Timer::Create(180.0f);

	SoundSource::Find("midnight-ride-01a")->Play(true);

	m_pFSM->Owner->Say(L"안녕하세요 사령관님!");
	m_pFSM->Owner->Say(L"이번엔 아군 함선들을 지휘해서\n함선들이 해운대에 상륙할 수\n있도록 도와주시면 됩니다.");
	m_pFSM->Owner->Say(L"이번 임무도 잘 수행해주세요.");

	SoundSource::Load("button-3", L"Sound/button-3.wav")->DuplicatePlay();
	m_pMissionPanelText->SetContext(L"모든 함선들을\n해운대로 정착시키자.");

	m_pBlackFadePanel->renderer->CurrentAnime->AnimeColor = Color::White;
	m_pBlackFadePanel->AddComponent<Fade<Color>>()->Set(Color(0, 0, 0, 0), FadeTarget::Renderer_Alpha, 0.006f);
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

	m_pBlackFadePanel->renderer->RenderType = RenderType::Rendering_UI;
	m_pBlackFadePanel->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Black")));
	m_pBlackFadePanel->renderer->Change(UnitStateType::Idle);

	m_pBlackFadePanel->transform->Position = Window::Center;
}

void PlayerControllerStage1::InputHelp()
{
	if (Input::GetKeyDown(KeyCode::Space))
	{
		m_pFSM->Owner->Say(L"도움이 필요하신가요?\n혹시 설명이 더 필요하다면 <H> 키를 눌러주세요.");
	}

	if (Input::GetKeyDown(KeyCode::H))
	{
		m_pFSM->Owner->Say(L"[!] 조작법\n* 마우스 좌클릭 - 범위 선택\n* 마우스 우클릭 - 선택된 객체 이동, 공격\n* 마우스 이동 - 카메라 이동");
	}
}

void PlayerControllerStage1::TimeUpdate()
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
