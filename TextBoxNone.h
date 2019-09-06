#pragma once
#include "BaseState.h"

class TextBox;

class TextBoxNone :
	public BaseState<TextBox>
{
private:
	Actor* m_pPanelBase = nullptr;
public:

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};

