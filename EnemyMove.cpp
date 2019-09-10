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
		return;
	}

	if (Base->m_bIsDetectedOnFrame_Attack == true)
	{
		ChangeState(UnitStateType::Attack);
		return;
	}

	Vector3 TargetPos = Base->m_pTarget->transform->Position;
	Vector3 This = Base->transform->Position;

	Vector3 Direction = TargetPos - This;

	float Length = Direction.Length();

	Direction.Normalize();

	// 스프라이트 방향 뒤집기
	if (Direction.x > 0)
	{
		Vector3 v = Base->transform->Scale;
		Base->transform->Scale = Vector3(fabs(v.x), v.y, v.y);
	}
	else if (Direction.x < 0)
	{
		Vector3 v = Base->transform->Scale;
		Base->transform->Scale = Vector3(-fabs(v.x), v.y, v.y);
	}

	m_pFSM->rigidbody->AddForce(Direction * Base->m_fSpeed * Time::Delta());
}

void EnemyMove::Exit()
{

}
