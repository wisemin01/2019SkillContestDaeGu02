#pragma once
#include "Renderer.h"

class LineRenderer :
	public Renderer
{
private:
	Vector2*	m_pLineArr = nullptr;
	Color		m_Color = Color::White;
	int			m_iCount = 0;
	int			m_iLineWidth = 10;
public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render();

	void Set(Vector2* lineArr, int count, int width = 10, Color color = Color::White);
};

