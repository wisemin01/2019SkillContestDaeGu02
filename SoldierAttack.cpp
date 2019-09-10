#include "DXUT.h"
#include "SoldierAttack.h"

#include "FSM.h"
#include "Soldier.h"
#include "Bullet.h"
#include "GuidedBullet.h"
#include "PlayerController.h"
#include "UnitAttackBase.h"

SoldierAttack::SoldierAttack()
{
	m_pAttackTimer = Timer::Create(0);
}

SoldierAttack::~SoldierAttack()
{
	Timer::Destroy(m_pAttackTimer);
	m_pAttackTimer = nullptr;
}

void SoldierAttack::Enter()
{
	m_pFSM->renderer->Change(UnitStateType::Attack);
}

void SoldierAttack::Stay()
{
	if (Base->m_pTarget == nullptr || Base->m_bIsDetectedOnFrame == false)
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

		Base->m_pAttacker->Attack(Base->m_iAttackDamage, Base->m_fAttackBulletSpeed, vThis, vDir, TagType::Enemy);

		m_pAttackTimer->Reset(Base->m_fAttackSpeed);
	}
}

void SoldierAttack::Exit()
{
	Base->m_pTarget = nullptr;
}
