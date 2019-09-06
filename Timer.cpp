#include "DXUT.h"
#include "Timer.h"

void Timer::Update(float delta)
{
	if (m_bIsEnd)
		return;

	if (m_bIsPause)
		return;

	m_fAnyTimes -= delta;

	if (m_fAnyTimes <= 0)
	{
		m_bIsEnd = true;
	}
}

Timer* Timer::Create(float time)
{
	Timer* timer = new Timer(time);

	m_listTimers.push_back(timer);

	return timer;
}

void Timer::Destroy(Timer* timer)
{
	m_listTimers.remove(timer);
	SAFE_DELETE(timer);
}

void Timer::UpdateTimers()
{
	float delta = Time::Delta();

	for (auto iter : m_listTimers)
	{
		iter->Update(delta);
	}
}

void Timer::Clear()
{
	for (auto iter : m_listTimers)
	{
		SAFE_DELETE(iter);
	}
	m_listTimers.clear();
}
