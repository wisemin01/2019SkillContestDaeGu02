#include "DXUT.h"
#include "OperatorUnit.h"

#include "OperatorIdle.h"
#include "OperatorTalk.h"

#include "FSM.h"
#include "TextBox.h"

void OperatorUnit::Initialize()
{
	renderer->RenderType = RenderType::Rendering_UI;
	renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Operator")->Get(1)));
	renderer->AddAnimation(UnitStateType::Talk, new Animation(Sprite::Find("Operator"), 0.225f));

	m_pFSM = AddComponent<FSM<OperatorUnit>>();
	m_pFSM->SetOwner(this);

	m_pFSM->AddState(UnitStateType::Idle, new OperatorIdle());
	m_pFSM->AddState(UnitStateType::Talk, new OperatorTalk());

	m_pFSM->ChangeState(UnitStateType::Idle);
}

void OperatorUnit::Update()
{
}

void OperatorUnit::Release()
{
}

void OperatorUnit::ConnectToTextBox(TextBox* textBox)
{
	m_pTextBox = textBox;

	m_pTextBox->SetTypingSpeed(0.075f);
	m_pTextBox->SetTypingEndWaitTime(0.5f);

	m_pTextBox->Insert(L"[!] �Ʊ��� �Լ����� �����ϸ�\n���� ������ּ���.");
	m_pTextBox->Insert(L"[!] ���� ��� óġ�ؾ߸�\n������ ���ư� �� �ֽ��ϴ�.");
	m_pTextBox->Insert(L"GO GO !!");
}
