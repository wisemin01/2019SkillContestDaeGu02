#include "DXUT.h"
#include "Character.h"

#include "Camera.h"

void Character::Initialize()
{
	AddComponent<Rigidbody>();
	AddComponent<Collider>();
}

void Character::Update()
{
}

void Character::Release()
{
	SAFE_DELETE(m_pAttacker);
}

void Character::OnDestroy()
{
	Camera::MainCamera()->Shake(0.5f, m_fShakePowerOnDeath);

	OnDeath(this->Base);
}

void Character::SetAttackType(UnitAttackBase* attack)
{
	m_pAttacker = attack;
}

void Character::Set(float speed, float attackSpeed, float bulletSpeed, float moveLimitRange, int attackDamage, Vector3 shotPos)
{
	m_fSpeed = speed;
	m_fAttackSpeed = attackSpeed;
	m_fAttackBulletSpeed = bulletSpeed;
	m_fMoveLimitRange = moveLimitRange;
	m_iAttackDamage = attackDamage;
	m_vShotPos = shotPos;
}
