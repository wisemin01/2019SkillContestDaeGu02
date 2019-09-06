#include "DXUT.h"
#include "OperatorIdle.h"

#include "FSM.h"
#include "OperatorUnit.h"
#include "TextBox.h"

void OperatorIdle::Enter()
{
	m_pFSM->Base->renderer->Change(UnitStateType::Idle);
}

void OperatorIdle::Stay()
{
	if (m_pFSM->Owner->m_pTextBox->GetCurrentState() == TypingType::Typing)
	{
		ChangeState(UnitStateType::Talk);
	}
}

void OperatorIdle::Exit()
{

}
