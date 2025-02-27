#pragma once
#include "UnitAttackBase.h"

class FireAttack :
	public UnitAttackBase
{
public:
	virtual void Attack(int damage, float bulletSpeed, Vector3 start, Vector3 direction, Tag targetTag) override;
};

