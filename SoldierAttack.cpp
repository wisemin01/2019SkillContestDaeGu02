#include "DXUT.h"
#include "SoldierAttack.h"

#include "FSM.h"
#include "Soldier.h"
#include "Bullet.h"
#include "PlayerController.h"

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
	}

	if (m_pAttackTimer->IsEnd == true)
	{
		Vector3 vTargetPos = Base->m_pTarget->transform->Position;
		Vector3 vThis = Base->transform->Position;

		Vector3 vDir = vTargetPos - vThis;

		vDir.Normalize();

		Actor* pBullet = ACTOR.Create(TagType::Effect, 4);
		pBullet->transform->Position = Base->transform->Position;
		pBullet->AddComponent<Bullet>()->Set(vDir, 40, TagType::Enemy, Base->m_iAttackDamage);

		m_pAttackTimer->Reset(Base->m_fAttackSpeed);
	}
}

void SoldierAttack::Exit()
{
	Base->m_pTarget = nullptr;
}
