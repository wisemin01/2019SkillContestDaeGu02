#pragma once
#include "BaseState.h"

class PlayerController;

class PlayerControllerStage2
	: public BaseState<PlayerController>
{
public:
	virtual void Enter() override;
	virtual void Stay() override;
	virtual void Exit() override;

	void CreateObjects();
};

