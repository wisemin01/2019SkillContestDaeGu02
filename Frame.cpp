#include "DXUT.h"
#include "Frame.h"

Frame::Frame()
{
	m_pFrameTimer = Timer::Create(0);
}

Frame::~Frame()
{
	Timer::Destroy(m_pFrameTimer);
}

void Frame::Set(int start, int end, float delay)
{
	m_pFrameTimer->Reset(delay);

	m_fDelay = delay;

	m_iStart = start;
	m_iEnd = end;
	m_iCurrent = start;
}

bool Frame::Update()
{
	if (m_pFrameTimer->IsEnd == true)
	{
		m_iCurrent++;

		m_pFrameTimer->Reset(m_fDelay);

		if (m_iCurrent >= m_iEnd)
		{
			m_iCurrent = m_iStart;
		}

		return true;
	}

	return false;
}
