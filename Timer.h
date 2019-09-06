#pragma once

class Timer
{
private:
	float m_fAnyTimes = 0.0f;
	bool m_bIsEnd = false;
	bool m_bIsPause = false;

public:

	Timer() {}
	Timer(float time) : m_fAnyTimes(time) {}
	~Timer() {}

	void Update(float delta);
	void Pause(bool value) { m_bIsPause = value; }
	void Reset(float time) { m_fAnyTimes = time; m_bIsEnd = false; }

	bool GetIsEnd() { return m_bIsEnd; }

	float GetAnyTime() { return m_fAnyTimes; }

	PropertyG(GetIsEnd)		bool IsEnd;
	PropertyG(GetAnyTime)	float AnyTime;

public:

	static Timer* Create(float time);
	static void Destroy(Timer* timer);
	static void UpdateTimers();
	static void Clear();

private:

	inline static std::list< Timer* > m_listTimers;
};

