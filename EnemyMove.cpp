#include "DXUT.h"
#include "EnemyMove.h"

#include "FSM.h"
#include "Enemy.h"

void EnemyMove::Enter()
{
	Base->renderer->Change(UnitStateType::Move);
}

void EnemyMove::Stay()
{
	if (Base->m_pTarget == nullptr
		|| Base->m_bIsDetectedOnFrame_Move == false)
	{
		ChangeState(UnitStateType::Idle);
	}

	if (Base->m_bIsDetectedOnFrame_Attack == true)
	{
		ChangeState(UnitStateType::Attack);
	}

	Vector3 TargetPos = Base->m_pTarget->transform->Position;
	Vector3 This = Base->transform->Position;

	Vector3 Direction = TargetPos - This;

	float Length = Direction.Length();

	Direction.Normalize();

	m_pFSM->rigidbody->AddForce(Direction * Base->m_fSpeed * Time::Delta());
}

void EnemyMove::Exit()
{

}
