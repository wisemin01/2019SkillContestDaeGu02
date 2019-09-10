#pragma once
#include "Component.h"

class SingleAnimation :
	public Component
{
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};

