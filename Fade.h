#pragma once
#include "Component.h"

class Fade :
	public Component
{
private:
public:

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};

