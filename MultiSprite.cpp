#include "DXUT.h"
#include "MultiSprite.h"

MultiSprite::~MultiSprite()
{
	for (auto iter : m_vecSprites)
	{
		SAFE_DELETE(iter);
	}

	m_vecSprites.clear();
}

void MultiSprite::Load(const std::string& path, int count)
{
	m_vecSprites.reserve(count);

	char Buffer[256] = { 0 };

	const char* Format = path.c_str();

	for (int i = 1; i <= count; i++)
	{
		sprintf(Buffer, Format, i);

		Sprite* Spr = new Sprite();

		Spr->Load(Buffer);

		m_vecSprites.push_back(Spr);
	}
}

Sprite* MultiSprite::Get(int count)
{
	if (count == -1)
	{
		return this;
	}
	else 
	{
		return m_vecSprites[count];
	}
}

int MultiSprite::Size()
{
	return m_vecSprites.size();
}
