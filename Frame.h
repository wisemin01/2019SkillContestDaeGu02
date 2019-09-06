#pragma once

class Timer;

class Frame
{
private:
	Timer* m_pFrameTimer = nullptr;

	int m_iStart = 0, m_iEnd = 0, m_iCurrent = 0;
	
	float m_fDelay = 0.0f;
public:
	Frame();
	~Frame();

	void Set(int start, int end, float delay);

	bool Update();

	bool GetIsLastFrame() { return m_iCurrent == (m_iEnd - 1); }

	int GetCurrentFrame()	{ return m_iCurrent;	}
	int GetStartFrame()		{ return m_iStart;		}
	int GetEndFrame()		{ return m_iEnd;		}

	PropertyG(GetCurrentFrame)	int CurrentFrame;
	PropertyG(GetStartFrame)	int StartFrame;
	PropertyG(GetEndFrame)		int EndFrame;
	PropertyG(GetIsLastFrame)	bool IsLastFrame;
};

