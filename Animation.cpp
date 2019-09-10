#include "DXUT.h"
#include "Animation.h"


Animation::Animation(Sprite* sprite, FrameRange range, float delay)
{
	m_pSprite = sprite;
	m_tFrame.Set(range.start, range.end, delay);
}

Animation::Animation(Sprite* sprite, float delay)
{
	m_pSprite = sprite;
	m_tFrame.Set(0, sprite->Size(), delay);
}

Animation::Animation(Sprite* sprite)
{
	m_pSprite = sprite;
	m_tFrame.Set(0, sprite->Size(), 0.0f);
}

bool Animation::Update()
{
	if (m_tFrame.Update())
	{
		if (m_tFrame.CurrentFrame == m_tFrame.StartFrame)
		{
			m_bIsEndOnThisFrame = true;
		}
		else
		{
			m_bIsEndOnThisFrame = false;
		}

		return true;
	}

	return false;
}

void Animation::Render()
{
	RENDER.CenterDraw(m_pSprite->Get(m_tFrame.CurrentFrame), m_tColor);
}
