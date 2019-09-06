#include "DXUT.h"
#include "SelectRange.h"

#include "LineRenderer.h"

void SelectRange::Initialize()
{
	m_pLineRenderer = AddComponent<LineRenderer>();
}

void SelectRange::Update()
{
	if (Input::GetKeyDown(KeyCode::LeftMouse))
	{
		m_vStart = ScreenToWorld(Input::GetMousePosition());
		m_vEnd = m_vStart;

		Base->IsVisible = true;
	}

	if (Input::GetKeyPress(KeyCode::LeftMouse)) 
	{
		m_vEnd = ScreenToWorld(Input::GetMousePosition());
	}

	if (Input::GetKeyUp(KeyCode::LeftMouse))
	{
		Base->IsVisible = false;

		RECT range;

		SetRect(&range,
			min(m_vStart.x, m_vEnd.x), 
			min(m_vStart.y, m_vEnd.y), 
			max(m_vStart.x, m_vEnd.x), 
			max(m_vStart.y, m_vEnd.y));

		OnSelect(range);
	}

	if (Base->IsVisible == true)
	{
		Vector2* line = new Vector2[5];

		line[0] = WorldToScreen(Vector2(m_vStart.x, m_vStart.y));
		line[1] = WorldToScreen(Vector2(m_vStart.x, m_vEnd.y));
		line[2] = WorldToScreen(Vector2(m_vEnd.x, m_vEnd.y));
		line[3] = WorldToScreen(Vector2(m_vEnd.x, m_vStart.y));
		line[4] = WorldToScreen(Vector2(m_vStart.x, m_vStart.y));

		m_pLineRenderer->Set(line, 5, 3, Color(0.0f, 1.0f, 0.917f, 0.8f));
	}
}

void SelectRange::Release()
{
}
