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

	m_pTextBox->Insert(L"[!] 아군의 함선들을 지휘하며\n지상에 상륙해주세요.");
	m_pTextBox->Insert(L"[!] 적을 모두 처치해야만\n앞으로 나아갈 수 있습니다.");
	m_pTextBox->Insert(L"GO GO !!");
}
