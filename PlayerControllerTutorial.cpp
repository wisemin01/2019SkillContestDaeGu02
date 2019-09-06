#include "DXUT.h"
#include "PlayerControllerTutorial.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "TextRenderer.h"

OperatorUnit* PlayerControllerTutorial::GetOperator()
{
	Actor* pBase = ACTOR.FindActor(TagType::Operator);

	if (pBase == nullptr)
		return nullptr;

	return pBase->GetComponent<OperatorUnit>();
}

void PlayerControllerTutorial::Enter()
{
	m_bIsStartTutorial = false;
	m_bIsQuest_Select = false;	

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

	if (m_bIsQuest_Select == false)
	{
		auto pOperator = GetOperator();

		if (pOperator->HasWork() == false)
		{
			m_pMissionPanelText->SetContext(L"���콺 ��Ŭ��(�巡��)�� �̿��ؼ�\n������ ��������.");
		}
	}
	else if (m_bIsQuest_Move == false)
	{
		auto pOperator = GetOperator();

		if (pOperator->HasWork() == false)
		{
			m_pMissionPanelText->SetContext(L"���콺 ��Ŭ���� �̿��ؼ�\n������ �̵���Ű��.");
		}
	}
	
	CheckEndTutorial();
	TimeUpdate();
}

void PlayerControllerTutorial::Exit()
{
	m_pFSM->Owner->OnSelect.Remove(OnSelect);
	m_pFSM->Owner->OnRightClick.Remove(OnMove);

	OnSelect = nullptr;
	OnMove = nullptr;
}

void PlayerControllerTutorial::Start()
{
	m_pFSM->Owner->m_pTimeAttackTimer = Timer::Create(180.0f);

	SoundSource::Find("midnight-ride-01a")->Play(true);

	m_pFSM->Owner->Say(L"�ȳ��ϼ��� ��ɰ���!");
	m_pFSM->Owner->Say(L"���� ���۷����͸� ����\n�ۡ��̶�� �մϴ�.");
	m_pFSM->Owner->Say(L"���ݺ��� ��ɰ��Բ�\n���۹��� �˷��帮���� �մϴ�.");
	m_pFSM->Owner->Say(L"�� ������ּ���.");
	m_pFSM->Owner->Say(L"�ϴ� ���콺 ��Ŭ������\n������ ������ ������\n�����غ�����.");

	m_bIsStartTutorial = true;
}

void PlayerControllerTutorial::CreateTutorialUI()
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

void PlayerControllerTutorial::Say_Tutorial_Text01()
{
	m_pMissionPanelText->SetContext(L"");

	m_pFSM->Owner->Say(L"�� �ϼ̾��!");
	m_pFSM->Owner->Say(L"���õ� �Լ�����\n���콺 ��Ŭ������ �̵���ų �� �־��.");
	m_pFSM->Owner->Say(L"���콺 ��Ŭ������\n�Լ����� �̵����Ѻ�����.");
}

void PlayerControllerTutorial::Say_Tutorial_Text02()
{
	m_pMissionPanelText->SetContext(L"");

	m_pFSM->Owner->Say(L"�� �ϼ̾��!");
	m_pFSM->Owner->Say(L"������ �����������.");
	m_pFSM->Owner->Say(L"�������ʹ� ���� ������\n�����ϰ� �ɰſ���.");
	m_pFSM->Owner->Say(L"�����ϼ̽��ϴ�.");
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

	if (pOperator->HasWork() == false)
	{
		SCENE.Change("STAGE1");
	}
}

void PlayerControllerTutorial::TimeUpdate()
{
	float anyTime = m_pFSM->Owner->m_pTimeAttackTimer->AnyTime;

	if (m_bIsWarningTimeAttack == false && anyTime <= 60.0f)
	{
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
