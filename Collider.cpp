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
	Vector3 s = transform->Scale;
	Vector3 p = transform->Position;

	s.x = fabsf(s.x);
	s.y = fabsf(s.y);
	s.z = fabsf(s.z);

	return {	(long)(m_rcRange.left	* s.x + p.x),
				(long)(m_rcRange.top	* s.y + p.y), 
				(long)(m_rcRange.right	* s.x + p.x), 
				(long)(m_rcRange.bottom * s.y + p.y)
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
