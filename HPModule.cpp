#include "DXUT.h"
#include "HPModule.h"

void HPModule::Initialize()
{

}

void HPModule::Update()
{

}

void HPModule::Release()
{

}

void HPModule::operator-=(int value)
{
	Minus(value);
}

void HPModule::operator+=(int value)
{
	Plus(value);
}

void HPModule::Minus(int value)
{
	m_iCurrent -= value;

	if (m_iCurrent < 0)
	{
		m_iCurrent = 0;

		if (m_bIsDeath == false)
		{
			m_bIsDeath = true;
			OnUnitDeath(EmptyEventArg());
		}
	}
}

void HPModule::Plus(int value)
{
	m_iCurrent += value;

	if (m_iCurrent > m_iMax)
		m_iCurrent = m_iMax;
}

void HPModule::Set(int hp)
{
	m_iCurrent = m_iMax = hp;
	m_bIsDeath = false;
}
