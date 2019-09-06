#include "DXUT.h"
#include "Animation.h"

Animation::Animation(Sprite* sprite, int start, int end, float delay)
{
	m_pSprite = sprite;
	m_tFrame.Set(start, end, delay);
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
		return true;
	}

	return false;
}

void Animation::Render()
{
	RENDER.CenterDraw(m_pSprite->Get(m_tFrame.CurrentFrame), m_tColor);
}
