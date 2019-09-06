#pragma once
#include "Sprite.h"
#include "Frame.h"

class Animation
{
private:
	Sprite* m_pSprite = nullptr;
	Frame	m_tFrame;
	Color	m_tColor = Color::White;
public:
	Animation(Sprite* sprite, int start, int end, float delay);
	Animation(Sprite* sprite, float delay);
	Animation(Sprite* sprite);
	~Animation() {}

	bool Update();
	void Render();

	Sprite* GetSprite() { return m_pSprite; }
	void SetColor(const Color& color) { m_tColor = color; }

	PropertyG(GetSprite)	Sprite* AnimeSprite;
	PropertyS(SetColor)		Color	AnimeColor;
};

