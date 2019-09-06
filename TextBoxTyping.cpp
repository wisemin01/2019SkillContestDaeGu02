#include "DXUT.h"
#include "TextBoxTyping.h"

#include "FSM.h"
#include "TextBox.h"
#include "TextRenderer.h"

void TextBoxTyping::Enter()
{
	m_pFSM->Owner->m_sNowContext.clear();

	m_sFinalContext = m_pFSM->Owner->m_queueContexts.front();
	m_pFSM->Owner->m_queueContexts.pop();

	m_iMaxIndex = m_sFinalContext.size() + 2;
	m_iCurrentIndex = 0;
	m_bIsWaiting = false;
	m_pWaitTimer = nullptr;

	m_Frame.Set(m_iCurrentIndex, m_iMaxIndex, m_pFSM->Owner->m_fTypingSpeed);

	m_pPanelBase = m_pFSM->Owner->transform->GetParent()->Base;
}

void TextBoxTyping::Stay()
{
	if (m_pPanelBase)
	{
		m_pPanelBase->transform->Scale =
			Vector3::Lerp(m_pPanelBase->transform->Scale, Vector3::One, 0.15f);

		if (m_pPanelBase->transform->Scale.x +
			m_pPanelBase->transform->Scale.y < 1.8f)
		{
			return;
		}
	}

	if (m_bIsWaiting == true)
	{
		if (m_pWaitTimer->IsEnd == true)
		{
			ChangeState(TypingType::None);
		}

		return;
	}

	if (m_Frame.Update())
	{
		m_pFSM->Owner->m_sNowContext = m_sFinalContext.substr(0, m_Frame.CurrentFrame);
		m_pFSM->Owner->m_pTextRenderer->SetContext(m_pFSM->Owner->m_sNowContext);

		m_pFSM->Owner->m_pTypingSoundSource->DuplicatePlay();

		if (m_Frame.IsLastFrame == true)
		{
			m_bIsWaiting = true;
			m_pWaitTimer = Timer::Create(m_pFSM->Owner->m_fTypingEndWaitTime);
		}
	}
}

void TextBoxTyping::Exit()
{
	m_sFinalContext.clear();
	m_pFSM->Owner->m_sNowContext.clear();

	Timer::Destroy(m_pWaitTimer);
	m_pWaitTimer = nullptr;
}
