#pragma once

class UnitAttackBase abstract
{
private:

public:

	virtual void Attack(int damage, float bulletSpeed, Vector3 start, Vector3 direction, Tag targetTag) = 0;
};

