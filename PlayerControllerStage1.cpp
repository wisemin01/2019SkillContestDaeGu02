#include "DXUT.h"
#include "PlayerControllerStage1.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "TextRenderer.h"

void PlayerControllerStage1::Enter()
{
	m_bIsStart = false;

	CreateStage1UI();
}

void PlayerControllerStage1::Stay()
{
	if (m_bIsStart == false)
	{
		Start();

		m_bIsStart = true;
	}
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

	m_pMissionPanelText->SetContext(L"��� �Լ�����\n�ؿ��� ������Ű��.");
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