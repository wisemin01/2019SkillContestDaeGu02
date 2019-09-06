#include "DXUT.h"
#include "TextBoxNone.h"

#include "FSM.h"
#include "TextBox.h"
#include "TextRenderer.h"

void TextBoxNone::Enter()
{
	m_pFSM->Owner->m_sNowContext.clear();
	m_pFSM->Owner->m_pTextRenderer->SetContext(L"");

	m_pPanelBase = m_pFSM->Owner->transform->GetParent()->Base;
}

void TextBoxNone::Stay()
{
	if (m_pPanelBase)
	{
		m_pPanelBase->transform->Scale =
			Vector3::Lerp(m_pPanelBase->transform->Scale, Vector3::Zero, 0.15f);
	}

	if (m_pFSM->Owner->m_queueContexts.empty() == false)
	{
		ChangeState(TypingType::Typing);
	}
}

void TextBoxNone::Exit()
{

}
