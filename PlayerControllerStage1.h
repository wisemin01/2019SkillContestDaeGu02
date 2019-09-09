#pragma once
#include "BaseState.h"

class PlayerController;
class TextRenderer;

class PlayerControllerStage1 :
	public BaseState<PlayerController>
{
private:
	bool m_bIsStart = false;
	bool m_bIsWarningTimeAttack = false;
	bool m_bIsWarningTimeEnd = false;

	TextRenderer* m_pTimePanelText = nullptr;
	TextRenderer* m_pMissionPanelText = nullptr;

	Actor* m_pBlackFadePanel = nullptr;

public:

	// BaseState을(를) 통해 상속됨
	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;

private:

	void Start();
	void CreateStage1UI();
	void InputHelp();
	void TimeUpdate();

	void CreateObjects();
};

