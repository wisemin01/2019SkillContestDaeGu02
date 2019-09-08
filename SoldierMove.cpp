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
	Vector3 EndPosition = m_pFSM->Owner->m_vEndPosition;
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
		Vector3 v = m_pFSM->Owner->transform->Scale;
		m_pFSM->Owner->transform->Scale = Vector3(fabs(v.x), v.y, v.y);
	}
	else
	{
		Vector3 v = m_pFSM->Owner->transform->Scale;
		m_pFSM->Owner->transform->Scale = Vector3(-fabs(v.x), v.y, v.y);
	}

	// Move ���°� �������� ����
	if (Length >= m_pFSM->Owner->m_fMoveLimitRange)
	{
		// ���� ������ ���� �������� �������� �ʾҴٸ� �̵��Ѵ�.
		m_pFSM->rigidbody->AddForce(Direction * m_pFSM->Owner->m_fSpeed * Time::Delta());
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
