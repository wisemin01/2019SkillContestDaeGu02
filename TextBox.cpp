#include "DXUT.h"
#include "TextBox.h"
#include "TextRenderer.h"
#include "FSM.h"

#include "TextBoxNone.h"
#include "TextBoxTyping.h"

void TextBox::Initialize()
{
	AddComponent<Transform>();

	m_pTextRenderer = AddComponent<TextRenderer>();
	m_pTextRenderer->Set("메이플스토리 Bold", 50, m_sNowContext);

	m_pFSM = AddComponent<FSM<TextBox>>();
	m_pFSM->SetOwner(this);
	
	m_pFSM->AddState(TypingType::None, new TextBoxNone());
	m_pFSM->AddState(TypingType::Typing, new TextBoxTyping());
	
	m_pFSM->ChangeState(TypingType::None);
}

void TextBox::Update()
{
	
}

void TextBox::Release()
{
}

void TextBox::Insert(const OutputString& context)
{
	m_queueContexts.push(context);
}

void TextBox::SetTypingSpeed(float delay)
{
	m_fTypingSpeed = delay;
}

void TextBox::SetTypingEndWaitTime(float delay)
{
	m_fTypingEndWaitTime = delay;
}

int TextBox::GetCurrentState()
{
	if (m_pFSM == nullptr)
		return -1;

	return m_pFSM->GetCurrentStatekey();
}
