#pragma once
#include "Component.h"

class HPModule :
	public Component
{
private:
	int m_iCurrent = 0;
	int m_iMax = 0;

	bool m_bIsDeath = false;

public:
	EventHandler<EmptyEventArg> OnUnitDeath;

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void operator -= (int value);
	void operator += (int value);

	void Plus(int value);
	void Minus(int value);

	void Set(int hp);
};

