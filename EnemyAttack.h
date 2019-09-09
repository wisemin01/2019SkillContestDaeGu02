#pragma once
#include "BaseState.h"

class Enemy;

class EnemyAttack :
	public BaseState<Enemy>
{
private:
	Timer* m_pAttackTimer = nullptr;
public:
	EnemyAttack();
	~EnemyAttack();

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};

