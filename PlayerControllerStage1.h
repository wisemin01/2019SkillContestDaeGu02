#pragma once
#include "BaseState.h"

class PlayerController;
class TextRenderer;

class PlayerControllerStage1 :
	public BaseState<PlayerController>
{
private:
	bool m_bIsStart = false;

	TextRenderer* m_pTimePanelText = nullptr;
	TextRenderer* m_pMissionPanelText = nullptr;

public:

	// BaseState을(를) 통해 상속됨
	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;

private:

	void Start();
	void CreateStage1UI();
	void InputHelp();
};

