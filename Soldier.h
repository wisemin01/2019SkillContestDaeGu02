#pragma once
#include "Character.h"

template <typename T>
class FSM;

class Soldier :
	public Character
{
	friend class SoldierIdle;
	friend class SoldierMove;
	friend class SoldierAttack;
private:
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

	void OnHpZero(EmptyEventArg e);

	void OnMoveCommand(Vector3 v);
	void OnSelectCommand(RECT rc);
	void OnDeselectCommand(EmptyEventArg e);
	void OnStopCommand(EmptyEventArg e);

	void OnRadarDetected(Collider* other);
	void CreateRadar(float width, float height);

private:

	void CreateSelectEffect();
};

