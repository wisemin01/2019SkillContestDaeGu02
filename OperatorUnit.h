#pragma once
#include "Component.h"

template <class T>
class FSM;
class TextBox;

class OperatorUnit :
	public Component
{
	friend class OperatorIdle;
	friend class OperatorTalk;
private:
	std::stack< std::string > m_stackTexts;
	
	FSM< OperatorUnit >	*	m_pFSM		= nullptr;
	TextBox	*				m_pTextBox	= nullptr;
public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void ConnectToTextBox(TextBox* textBox);
};

