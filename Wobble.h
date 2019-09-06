#pragma once
#include "Component.h"

// 특정 방향으로 흔들리는 움직임을 만들어주는 객체
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

