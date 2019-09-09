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
#include "Trigger.h"

void PlayerControllerTutorial::Say_Tutorial_Text01()
{
	m_pMissionPanelText->SetContext(L"���� �̼��� �����ϴ�.");

	SoundSource::Load("mission-success", L"Sound/mission-success.wav")->Play();

	Base->Say(L"�� �ϼ̾��!");
	Base->Say(L"���õ� �Լ�����\n���콺 ��Ŭ������ �̵���ų �� �־��.");
	Base->Say(L"���콺 ��Ŭ������\n�Լ����� �̵����Ѻ�����.");

	m_bIsDisplayQuest[1] = true;
}

void PlayerControllerTutorial::Say_Tutorial_Text02()
{
	m_pMissionPanelText->SetContext(L"���� �̼��� �����ϴ�.");

	SoundSource::Load("mission-success", L"Sound/mission-success.wav")->Play();

	Base->Say(L"�� �ϼ̾��!");
	Base->Say(L"���� �Լ����� �̵�����\n�� �Լ����� ã��\n��� �ı����ּ���.");
	Base->Say(L"�� �Լ����� ��� óġ�ؾ�\n�ؿ�뿡 �Լ�����\n���ڽ�ų �� �־��.");
	
	m_bIsDisplayQuest[2] = true;
}

void PlayerControllerTutorial::Say_Tutorial_Text03(bool flag)
{
	m_pMissionPanelText->SetContext(L"���� �̼��� �����ϴ�.");

	if (flag == true) 
	{
		Base->Say(L"�� �ϼ̾��!");
		Base->Say(L"���� �˷��帮�� �� �����������.\n�����ϼ̽��ϴ�.");
		Base->Say(L"���� ���������� �Լ�����\n�̵����Ѽ� �踦 ���ڽ��� �ּ���.");

		m_pStageEndTrigger = ACTOR.Create(TagType::None);

		auto trigger = m_pStageEndTrigger->AddComponent<Trigger>();
		trigger->collider->SetRange(300, 1125);
		trigger->OnTriggerStay += CreateListener(Collider*, OnAnchorCommand);

		m_pStageEndTrigger->transform->Position = Vector3(1900, 562.5, 0);

		m_bIsDisplayQuest[3] = true;
	}
	else
	{
		Base->Say(L"�Ʊ��� �Լ��� ��� �ı��Ǿ����...");
		Base->Say(L"��� �� �ٽ� ������ ���۵��״�\n���ݸ� �� ������ ���ּ���.");

		m_bIsTutorialFailed = true;
	}
}
