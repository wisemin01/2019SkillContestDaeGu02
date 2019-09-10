#pragma once
#include "BaseState.h"

class PlayerController;
class TextRenderer;
class OperatorUnit;

class PlayerControllerStage1 :
	public BaseState<PlayerController>
{
private:
	bool m_bIsStart = false;
	bool m_bIsWarningTimeAttack = false;
	bool m_bIsWarningTimeEnd = false;
	bool m_bIsQuestClear = false;
	bool m_bIsQuestFail = false;
	bool m_bIsStageEnd = false;

	bool m_bIsWarning = false;
	bool m_bIsCheering = false;

	TextRenderer* m_pTimePanelText = nullptr;
	TextRenderer* m_pMissionPanelText = nullptr;

	Actor* m_pBlackFadePanel = nullptr;

public:

	// BaseState을(를) 통해 상속됨
	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;

	void OnStageEndTrigger(Collider* other);

private:

	void Start();
	void CreateStage1UI();
	void InputHelp();
	void TimeUpdate();
	void StatusUpdate();

	void CreateObjects();

	OperatorUnit* GetOperator();
};

