#include "DXUT.h"
#include "SoldierIdle.h"

#include "FSM.h"
#include "Soldier.h"

void SoldierIdle::Enter()
{
	m_pFSM->renderer->Change(UnitStateType::Idle);
}

void SoldierIdle::Stay()
{
	if (Base->m_bIsDetectedOnFrame == true)
	{
		ChangeState(UnitStateType::Attack);
	}
}

void SoldierIdle::Exit()
{

}
