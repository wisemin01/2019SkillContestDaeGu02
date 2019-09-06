#pragma once
#include "Component.h"

// Ư�� �������� ��鸮�� �������� ������ִ� ��ü
class Wobble
	: public Component
{
private:
	int m_iWobbleType = WobbleType::None;

	float m_fPower = 0;
	float m_fMoveStack = 0;
	float m_fMoveLimit = 0;

	bool m_bMoveFlag = true;
public:
	Wobble() {}
	~Wobble() {}

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void Set(float wobbleType, float power, float moveLimit);
};

