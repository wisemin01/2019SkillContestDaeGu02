#include "DXUT.h"
#include "OperatorTalk.h"

#include "FSM.h"
#include "OperatorUnit.h"
#include "TextBox.h"

void OperatorTalk::Enter()
{
	m_pFSM->Base->renderer->Change(UnitStateType::Talk);
}

void OperatorTalk::Stay()
{
	if (m_pFSM->Owner->m_pTextBox->GetCurrentState() == TypingType::None)
	{
		ChangeState(UnitStateType::Idle);
	}
}

void OperatorTalk::Exit()
{
}
