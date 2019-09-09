#include "DXUT.h"
#include "OperatorTalk.h"

#include "FSM.h"
#include "OperatorUnit.h"
#include "TextBox.h"

void OperatorTalk::Enter()
{
	m_pFSM->Base->renderer->Change(UnitStateType::Talk);

	SoundSource::Load("button-34", L"Sound/button-34.wav")->Play();
}

void OperatorTalk::Stay()
{
	if (Base->m_pTextBox->GetCurrentState() == TypingType::None)
	{
		ChangeState(UnitStateType::Idle);
	}
}

void OperatorTalk::Exit()
{
}
