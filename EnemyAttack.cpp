#include "DXUT.h"
#include "EnemyAttack.h"

#include "FSM.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UnitAttackBase.h"

EnemyAttack::EnemyAttack()
{
	m_pAttackTimer = Timer::Create(0);
}

EnemyAttack::~EnemyAttack()
{
	Timer::Destroy(m_pAttackTimer);
	m_pAttackTimer = nullptr;
}

void EnemyAttack::Enter()
{
	Base->renderer->Change(UnitStateType::Attack);
}

void EnemyAttack::Stay()
{
	if (Base->m_pTarget == nullptr || Base->m_bIsDetectedOnFrame_Attack == false)
	{
		ChangeState(UnitStateType::Idle);
		return;
	}

	if (m_pAttackTimer->IsEnd == true)
	{
		bool flip = Base->transform->Scale.x < 0;

		Vector3 vTargetPos = Base->m_pTarget->transform->Position;
		Vector3 vThis = Base->transform->Position + (flip ? Vector3::XFlip(Base->m_vShotPos) : Base->m_vShotPos);

		Vector3 vDir = vTargetPos - vThis;

		vDir.Normalize();

		Base->m_pAttacker->Attack(Base->m_iAttackDamage, Base->m_fAttackBulletSpeed, vThis, vDir, TagType::Player);

		m_pAttackTimer->Reset(Base->m_fAttackSpeed);
	}
}

void EnemyAttack::Exit()
{
	Base->m_pTarget = nullptr;
}
