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

	// ���� ����
	Vector3 Direction = EndPosition - CurrentPosition;

	// �Ÿ� ����
	float Length = Direction.Length();

	// ���� ����ȭ
	Direction.Normalize();
	
	// ��������Ʈ ���� ������
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

	// Move ���°� �������� ����
	if (Length >= Base->m_fMoveLimitRange)
	{
		// ���� ������ ���� �������� �������� �ʾҴٸ� �̵��Ѵ�.
		m_pFSM->rigidbody->AddForce(Direction * Base->m_fSpeed * Time::Delta());
	}
	else
	{
		// ���� ���� ���Դٸ� IDLE ���·� ��ȯ�Ѵ�.
		ChangeState(UnitStateType::Idle);
	}
}

void SoldierMove::Exit()
{

}
