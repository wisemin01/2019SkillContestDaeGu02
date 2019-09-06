#include "DXUT.h"
#include "Collider.h"

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_CIRCLE)
Circle Collider::GetWorldRange()
{
	return Circle(transform->Position,
		m_fRadius * max(transform->Scale.x, transform->Scale.y));
}
#endif

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_RECT)
RECT Collider::GetWorldRange()
{
	return {	(long)(m_rcRange.left	* transform->Scale.x + transform->Position.x),
				(long)(m_rcRange.top	* transform->Scale.y + transform->Position.y), 
				(long)(m_rcRange.right	* transform->Scale.x + transform->Position.x), 
				(long)(m_rcRange.bottom * transform->Scale.y + transform->Position.y)
	};
}

void Collider::SetRange(float width, float height)
{
	::SetRect(&m_rcRange, -Half(width), -Half(height), Half(width), Half(height));
}
#endif

void Collider::Initialize()
{
	Base->collider = this;

	COLLISION.Register(this);
}

void Collider::Update()
{
}

void Collider::Release()
{
	if (Base->collider == this)
		Base->collider = nullptr;

	COLLISION.Unregister(this);
}
