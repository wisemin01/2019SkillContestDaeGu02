#pragma once
#include "Component.h"

class Fade :
	public Component
{
private:
public:

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};

