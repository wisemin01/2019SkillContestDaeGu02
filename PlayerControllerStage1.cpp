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

	m_pFSM->Owner->Say(L"�ȳ��ϼ��� ��ɰ���!");
	m_pFSM->Owner->Say(L"�̹��� �Ʊ� �Լ����� �����ؼ�\n�Լ����� �ؿ�뿡 ����� ��\n�ֵ��� �����ֽø� �˴ϴ�.");
	m_pFSM->Owner->Say(L"�̹� �ӹ��� �� �������ּ���.");

	SoundSource::Load("button-3", L"Sound/button-3.wav")->DuplicatePlay();
	m_pMissionPanelText->SetContext(L"��� �Լ�����\n�ؿ��� ������Ű��.");

	m_pBlackFadePanel->renderer->CurrentAnime->AnimeColor = Color::White;
	m_pBlackFadePanel->AddComponent<Fade<Color>>()->Set(Color(0, 0, 0, 0), FadeTarget::Renderer_Alpha, 0.006f);
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

	m_pBlackFadePanel->renderer->RenderType = RenderType::Rendering_UI;
	m_pBlackFadePanel->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Black")));
	m_pBlackFadePanel->renderer->Change(UnitStateType::Idle);

	m_pBlackFadePanel->transform->Position = Window::Center;
}

void PlayerControllerStage1::InputHelp()
{
	if (Input::GetKeyDown(KeyCode::Space))
	{
		m_pFSM->Owner->Say(L"������ �ʿ��ϽŰ���?\nȤ�� ������ �� �ʿ��ϴٸ� <H> Ű�� �����ּ���.");
	}

	if (Input::GetKeyDown(KeyCode::H))
	{
		m_pFSM->Owner->Say(L"[!] ���۹�\n* ���콺 ��Ŭ�� - ���� ����\n* ���콺 ��Ŭ�� - ���õ� ��ü �̵�, ����\n* ���콺 �̵� - ī�޶� �̵�");
	}
}

void PlayerControllerStage1::TimeUpdate()
{
	float anyTime = m_pFSM->Owner->m_pTimeAttackTimer->AnyTime;

	if (m_bIsWarningTimeAttack == false && anyTime <= 60.0f)
	{
		SoundSource::Load("beep-warning", L"Sound/beep-warning.wav")->Play();

		m_bIsWarningTimeAttack = true;
		m_pFSM->Owner->Say(L"�ð��� �� ���� �ʾҾ��!\n���ѷ��ּ���.");
		m_pTimePanelText->SetColor(Color::Red);
	}

	if (m_bIsWarningTimeEnd == false && anyTime <= 0.0f)
	{
		m_bIsWarningTimeEnd = true;
		m_pFSM->Owner->Say(L"�ð��� �� �Ǿ����.....\n�ӹ� �����Դϴ�.....");
		m_pTimePanelText->SetColor(Color::Black);
	}

	m_pTimePanelText->SetContext(SecondsToTimeStringW(anyTime));
}
