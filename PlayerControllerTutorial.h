#pragma once
#include "BaseState.h"

class PlayerController;
class TextRenderer;
class OperatorUnit;

class PlayerControllerTutorial :
	public BaseState<PlayerController>
{
private:

	bool m_bIsStartTutorial		= false;
	bool m_bIsQuest_Select		= false;
	bool m_bIsQuest_Move		= true;
	bool m_bIsEndListenTutorial = false;
	bool m_bIsWarningTimeAttack = false;
	bool m_bIsWarningTimeEnd	= false;
	bool m_bIsBlackFadeEnd		= false;

	bool m_bIsDisplayQuest[2]	= { false };

	TextRenderer* m_pTimePanelText = nullptr;
	TextRenderer* m_pMissionPanelText = nullptr;

	Actor* m_pBlackFadePanel = nullptr;

	OperatorUnit* GetOperator();

private:

	EventListener<RECT>* OnSelect;
	EventListener<Vector3>* OnMove;

public:

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;

private:
	void Start();
	void CreateTutorialUI();

	void Say_Tutorial_Text01();
	void Say_Tutorial_Text02();

	void OnSelectCommand(RECT rc);
	void OnMoveCommand(Vector3 v);

	void CheckEndTutorial();
	void CheckDisplayQuest();
	void TimeUpdate();
};

