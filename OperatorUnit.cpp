#include "DXUT.h"
#include "OperatorUnit.h"

#include "OperatorIdle.h"
#include "OperatorTalk.h"

#include "PlayerController.h"

#include "FSM.h"
#include "TextBox.h"

void OperatorUnit::Initialize()
{
	renderer->RenderType = RenderType::UI;
	renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Operator")->Get(1)));
	renderer->AddAnimation(UnitStateType::Talk, new Animation(Sprite::Find("Operator"), 0.2f));

	m_pFSM = AddComponent<FSM<OperatorUnit>>();
	m_pFSM->SetOwner(this);

	m_pFSM->AddState(UnitStateType::Idle, new OperatorIdle());
	m_pFSM->AddState(UnitStateType::Talk, new OperatorTalk());

	m_pFSM->ChangeState(UnitStateType::Idle);

	OnTalkListen = CreateListener(OutputString, Say);

	PlayerController::GetMain()->OnTalk += OnTalkListen;
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

	m_pTextBox->SetTypingSpeed(0.025f);
	m_pTextBox->SetTypingEndWaitTime(0.8f);
}

void OperatorUnit::Say(const OutputString& context)
{
	m_pTextBox->Insert(context);
}

int OperatorUnit::GetFSMState()
{
	return m_pFSM->GetCurrentStatekey();
}

bool OperatorUnit::HasWork()
{
	return (GetFSMState() == UnitStateType::Talk) || (m_pTextBox->IsEmpty() == false);
}
