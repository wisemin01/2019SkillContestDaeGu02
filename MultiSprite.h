#pragma once
#include "Sprite.h"

class MultiSprite :
	public Sprite
{
private:
	std::vector< Sprite* > m_vecSprites;
public:
	MultiSprite() : Sprite() {}
	virtual ~MultiSprite();

	virtual void	Load(const std::string& path, int count = 0) override;
	virtual Sprite* Get(int count = -1) override;
	virtual int		Size() override;
};

