#include "DXUT.h"
#include "TextBoxNone.h"

#include "FSM.h"
#include "TextBox.h"
#include "TextRenderer.h"

void TextBoxNone::Enter()
{
	Base->m_sNowContext.clear();
	Base->m_pTextRenderer->SetContext(L"");

	m_pPanelBase = Base->transform->GetParent()->Base;
}

void TextBoxNone::Stay()
{
	if (m_pPanelBase)
	{
		m_pPanelBase->transform->Scale =
			Vector3::Lerp(m_pPanelBase->transform->Scale, Vector3::Zero, 0.15f);
	}

	if (Base->m_queueContexts.empty() == false)
	{
		ChangeState(TypingType::Typing);
	}
}

void TextBoxNone::Exit()
{

}
