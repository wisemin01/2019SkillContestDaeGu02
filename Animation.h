#pragma once
#include "Sprite.h"
#include "Frame.h"

struct FrameRange
{
	int start;
	int end;
	FrameRange(int s, int e)
		:start(s), end(e) {}
};

class Animation
{
private:
	Sprite* m_pSprite = nullptr;
	Frame	m_tFrame;
	Color	m_tColor = Color::White;

	bool	m_bIsEndOnThisFrame = false;
public:
	Animation(Sprite* sprite, FrameRange range, float delay);
	Animation(Sprite* sprite, float delay);
	Animation(Sprite* sprite);
	~Animation() {}

	bool Update();
	void Render();

	void SetSprite(Sprite* sprite) { m_pSprite = sprite; }
	Sprite* GetSprite() { return m_pSprite; }

	void SetColor(const Color& color) { m_tColor = color; }
	Color GetColor() { return m_tColor; }

	float GetAlpha() { return m_tColor.a; }
	void SetAlpha(float value) { m_tColor.a = value; }

	bool GetIsEnd() { return m_bIsEndOnThisFrame; }

	PropertyGS(GetSprite, SetSprite)	Sprite* AnimeSprite;
	PropertyGS(GetColor, SetColor)		Color	AnimeColor;
	PropertyG(GetIsEnd)					bool	IsEndOnThisFrame;
};

