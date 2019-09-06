#pragma once

class Time
{
private:

	inline static float g_fTimeScale = 1.0f;

public:

	static float Current() { return g_fNowTime; }
	static float Delta() { return g_fDeltaTime * g_fTimeScale; }

	static void SetTimeScale(float value) { g_fTimeScale = value; }
	static float GetTimeScale() { return g_fTimeScale; }
};

