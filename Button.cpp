#include "DXUT.h"
#include "Button.h"

void Button::Initialize()
{
	SetRange();
}

void Button::Update()
{
	Vector3 mouse = Input::GetMousePosition();

	if (renderer && renderer->RenderType == RenderType::ObjectSpace)
	{
		mouse = ScreenToWorld(mouse);
	}

	bool result = PointInRect(&GetWorldRange(), &mouse);

	if (result)
	{
		if (m_bIsGrowOnMouseCursor)
		{
			transform->Scale = Lerp(transform->Scale, Vector3(1.1, 1.1, 1.1), 0.1);
		}

		if (Input::GetKeyDown(KeyCode::LeftMouse))
		{
			OnButtonClick(EmptyEventArg());
		}
	}
	else if(m_bIsGrowOnMouseCursor)
	{
		transform->Scale = Lerp(transform->Scale, Vector3::One, 0.1);
	}
}

void Button::Release()
{
}

void Button::SetRange(float width, float height)
{
	SetRect(&m_rcButtonRange, -Half(width), -Half(height), Half(width), Half(width));
}

void Button::SetRange()
{
	float w = renderer->CurrentAnime->AnimeSprite->Width;
	float h = renderer->CurrentAnime->AnimeSprite->Height;

	SetRange(w, h);
}

RECT Button::GetWorldRange()
{
	Vector3 s = transform->Scale;
	Vector3 p = transform->Position;

	s.x = fabsf(s.x);
	s.y = fabsf(s.y);
	s.z = fabsf(s.z);

	return {	(long)(m_rcButtonRange.left * s.x + p.x),
				(long)(m_rcButtonRange.top * s.y + p.y),
				(long)(m_rcButtonRange.right * s.x + p.x),
				(long)(m_rcButtonRange.bottom * s.y + p.y)
	};
}
