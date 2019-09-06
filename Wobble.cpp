#include "DXUT.h"
#include "Wobble.h"

void Wobble::Initialize()
{
	AddComponent<Rigidbody>();
}

void Wobble::Update()
{
	float prevIndex = m_fMoveStack;

	if (m_bMoveFlag)
	{
		m_fMoveStack += m_fPower * Time::Delta();

		if (m_fMoveStack >= m_fMoveLimit)
			m_bMoveFlag = !m_bMoveFlag;
	}
	else
	{
		m_fMoveStack -= m_fPower * Time::Delta();

		if (m_fMoveStack <= -m_fMoveLimit)
			m_bMoveFlag = !m_bMoveFlag;
	}

	float move = m_fMoveStack - prevIndex;

	if (m_iWobbleType == WobbleType::Width)
		rigidbody->AddForce(Vector3(move, 0, 0));
	else if(m_iWobbleType == WobbleType::Height)
		rigidbody->AddForce(Vector3(0, move, 0));
}

void Wobble::Release()
{
}

void Wobble::Set(float wobbleType, float power, float moveLimit)
{
	m_iWobbleType = wobbleType;
	m_fPower = power;
	m_fMoveLimit = moveLimit;
	m_fMoveStack = 0;
	m_bMoveFlag = true;
}