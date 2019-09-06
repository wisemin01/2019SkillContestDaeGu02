#pragma once
#include "BaseState.h"

class Soldier;

class SoldierMove :
	public BaseState<Soldier>
{
	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};

