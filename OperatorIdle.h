#pragma once
#include "BaseState.h"

class OperatorUnit;

class OperatorIdle :
	public BaseState<OperatorUnit>
{
public:

	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;
};

