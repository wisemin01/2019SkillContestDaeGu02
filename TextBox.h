#pragma once
#include "Component.h"

template <typename T>
class FSM;
class TextRenderer;

class TextBox :
	public Component
{
	friend class TextBoxNone;
	friend class TextBoxTyping;
private:
	std::queue< OutputString > m_queueContexts;
	OutputString m_sNowContext;

	float m_fTypingSpeed = 0.3f;
	float m_fTypingEndWaitTime = 1.0f;

	FSM<TextBox>* m_pFSM = nullptr;
	TextRenderer* m_pTextRenderer = nullptr;
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void Insert(const OutputString& context);
	void SetTypingSpeed(float delay);
	void SetTypingEndWaitTime(float delay);

	int GetCurrentState();
};

