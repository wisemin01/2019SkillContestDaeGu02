#include "DXUT.h"
#include "EnemyIdle.h"

#include "FSM.h"
#include "Enemy.h"

void EnemyIdle::Enter()
{
	Base->renderer->Change(UnitStateType::Idle);
}

void EnemyIdle::Stay()
{
	if (Base->m_bIsDetectedOnFrame_Attack == true)
	{
		ChangeState(UnitStateType::Attack);
		return;
	}

	if (Base->m_bIsDetectedOnFrame_Move == true)
	{
		ChangeState(UnitStateType::Move);
		return;
	}
}

void EnemyIdle::Exit()
{

}
