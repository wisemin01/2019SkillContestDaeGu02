#pragma once
#include "BaseState.h"

class Enemy;

class EnemyMove :
	public BaseState<Enemy>
{
public:

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};

