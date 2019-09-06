#pragma once
#include "BaseState.h"

class TextBox;

class TextBoxTyping :
	public BaseState<TextBox>
{
private:
	int m_iMaxIndex = 0;
	int m_iCurrentIndex = 0;

	bool m_bIsWaiting = false;

	Frame m_Frame;
	Timer* m_pWaitTimer = nullptr;

	OutputString m_sFinalContext;

private:
	Actor* m_pPanelBase = nullptr;

public:
	TextBoxTyping() {}
	virtual ~TextBoxTyping() {}

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};

