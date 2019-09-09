#pragma once
#include "BaseState.h"

class Soldier;

class SoldierAttack :
	public BaseState<Soldier>
{
private:
	Timer* m_pAttackTimer = nullptr;
public:
	SoldierAttack();
	~SoldierAttack();

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};

