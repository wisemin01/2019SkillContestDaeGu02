#pragma once
#include "Character.h"

template <class T>
class FSM;
class UnitRadar;

class Enemy :
	public Character
{
	friend class EnemyIdle;
	friend class EnemyMove;
	friend class EnemyAttack;
private:
	bool	m_bIsSelect = false;
	bool	m_bIsDetectedOnFrame_Move = false;
	bool	m_bIsDetectedOnFrame_Attack = false;

	Actor*	m_pAttackRadar = nullptr;
	Actor*	m_pMoveRadar = nullptr;
	Actor*	m_pTarget = nullptr;

	FSM<Enemy>* m_pFSM = nullptr;

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void OnDestroy() override;

	void OnRadarDetected_Move(Collider* other);
	void OnRadarDetected_Attack(Collider* other);

	void OnHpZero(EmptyEventArg e);
public:

	void CreateMoveRadar(float width, float height);
	void CreateAttackRadar(float width, float height);
};

