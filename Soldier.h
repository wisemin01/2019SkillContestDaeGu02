#pragma once
#include "Component.h"

template <typename T>
class FSM;

class Soldier :
	public Component
{
	friend class SoldierIdle;
	friend class SoldierMove;
	friend class SoldierAttack;
private:
	float m_fSpeed = 100.0f;
	float m_fAttackSpeed = 0.7f;
	float m_fMoveLimitRange = 100.0f;
	
	int m_iAttackDamage = 10;
	int m_iState = UnitStateType::None;

	bool m_bIsSelect = false;
	bool m_bIsDetectedOnFrame = false;

	Vector3 m_vEndPosition = Vector3::Zero;

	FSM<Soldier>* m_pFSM = nullptr;

	Actor* m_pSelectEffect = nullptr;
	Actor* m_pRadar = nullptr;
	Actor* m_pTarget = nullptr;

public:

	EventListener<Vector3>		 * OnRightClick;
	EventListener<RECT>			 * OnSelect;
	EventListener<EmptyEventArg> * OnDeselect;
	EventListener<EmptyEventArg> * OnStop;

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

	virtual void OnDestroy() override;
	virtual void OnCollision(Collider* other) override;

	void OnHpZero(EmptyEventArg e);

	void OnMoveCommand(Vector3 v);
	void OnSelectCommand(RECT rc);
	void OnDeselectCommand(EmptyEventArg e);
	void OnStopCommand(EmptyEventArg e);

	void OnRadarDetected(Collider* other);

private:

	void CreateSelectEffect();
	void CreateRadar(float width, float height);
};

