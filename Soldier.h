#pragma once
#include "Component.h"

template <typename T>
class FSM;

class Soldier :
	public Component
{
	friend class SoldierIdle;
	friend class SoldierMove;
private:
	float m_fSpeed = 100.0f;
	float m_fMoveLimitRange = 100.0f;
	
	int m_iState = UnitStateType::None;

	bool m_bIsSelect = false;

	Vector3 m_vEndPosition = Vector3::Zero;

	FSM<Soldier>* m_pFSM = nullptr;

public:

	EventListener<Vector3>		 * OnRightClick;
	EventListener<RECT>			 * OnSelect;
	EventListener<EmptyEventArg> * OnDeselect;
	EventListener<EmptyEventArg> * OnStop;

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void OnDestroy() override;
	virtual void OnCollision(Collider* other) override;

	void OnMoveCommand(Vector3 v);
	void OnSelectCommand(RECT rc);
	void OnDeselectCommand(EmptyEventArg e);
	void OnStopCommand(EmptyEventArg e);
};

