#pragma once
#include "Component.h"

class UnitAttackBase;

class Character :
	public Component
{
protected:
	float m_fSpeed = 100.0f;
	float m_fAttackSpeed = 0.7f;
	float m_fAttackBulletSpeed = 120.0f;
	float m_fMoveLimitRange = 100.0f;
	float m_fShakePowerOnDeath = 20.0f;

	int m_iAttackDamage = 10;
	int m_iState = UnitStateType::None;

	Vector3 m_vShotPos = Vector3::Zero;

	UnitAttackBase* m_pAttacker = nullptr;

public:

	EventHandler<Actor*> OnDeath;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void OnDestroy() override;

	void Set(float speed, float attackSpeed, float bulletSpeed, float moveLimitRange, int attackDamage,
		Vector3 shotPos);
	void SetShakePowerOnDeath(float value) { m_fShakePowerOnDeath = value; }

	void SetAttackType(UnitAttackBase* attack);
};

