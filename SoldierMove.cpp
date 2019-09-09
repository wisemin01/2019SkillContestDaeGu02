#include "DXUT.h"
#include "SoldierMove.h"

#include "FSM.h"
#include "Soldier.h"

void SoldierMove::Enter()
{
	m_pFSM->renderer->Change(UnitStateType::Move);
}

void SoldierMove::Stay()
{
	Vector3 EndPosition = Base->m_vEndPosition;
	Vector3 CurrentPosition = m_pFSM->transform->Position;

	// 방향 검출
	Vector3 Direction = EndPosition - CurrentPosition;

	// 거리 검출
	float Length = Direction.Length();

	// 방향 정규화
	Direction.Normalize();
	
	// 스프라이트 방향 뒤집기
	if (Direction.x > 0)
	{
		Vector3 v = Base->transform->Scale;
		Base->transform->Scale = Vector3(fabs(v.x), v.y, v.y);
	}
	else if(Direction.x < 0)
	{
		Vector3 v = Base->transform->Scale;
		Base->transform->Scale = Vector3(-fabs(v.x), v.y, v.y);
	}

	// Move 상태가 끝났는지 검증
	if (Length >= Base->m_fMoveLimitRange)
	{
		// 아직 움직임 상한 범위까지 움직이지 않았다면 이동한다.
		m_pFSM->rigidbody->AddForce(Direction * Base->m_fSpeed * Time::Delta());
	}
	else
	{
		// 범위 내로 들어왔다면 IDLE 상태로 전환한다.
		ChangeState(UnitStateType::Idle);
	}
}

void SoldierMove::Exit()
{

}
