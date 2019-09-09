#pragma once
#include "Component.h"

template <class T>
class FSM;
class UnitRadar;

class Enemy :
	public Component
{
	friend class EnemyIdle;
	friend class EnemyMove;
	friend class EnemyAttack;
private:
	float	m_fSpeed = 100.0f;
	float	m_fMoveLimitRange = 100.0f;
	float	m_fAttackSpeed = 0.7f;
	float	m_fAttackBulletSpeed = 120.0f;

	int		m_iAttackDamage = 10;
	int		m_iState = UnitStateType::None;

	bool	m_bIsSelect = false;
	bool	m_bIsDetectedOnFrame_Move = false;
	bool	m_bIsDetectedOnFrame_Attack = false;

	Vector3 m_vShotPos = Vector3::Zero;

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

	void Set(float speed, float attackSpeed, float bulletSpeed, float moveLimitRange, int attackDamage,
		Vector3 shotPos);
private:

	void CreateMoveRadar(float width, float height);
	void CreateAttackRadar(float width, float height);
};

