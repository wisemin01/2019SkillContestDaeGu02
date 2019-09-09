#pragma once
#include "Component.h"

class Collider :
	public Component
{
private:

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_CIRCLE)
	float m_fRadius = 0.0f;
#endif

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_RECT)
	RECT m_rcRange = { 0 };
#endif

	bool m_bIsTrigger = false;

public:

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	bool GetIsTrigger() { return m_bIsTrigger; }
	void SetIsTrigger(bool value) { m_bIsTrigger = value; }

	Tag GetTag() { return Base->m_Tag; }

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_CIRCLE)

	Circle GetWorldRange();

	void SetRadius(float value) { m_fRadius = value; }
	float GetRadius() { return m_fRadius; }

#endif

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_RECT)

	RECT GetWorldRange();

	void SetRect(RECT value) { m_rcRange = value; }
	RECT GetRect() { return m_rcRange; }

	void SetRange(float width, float height);

#endif

public:
#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_CIRCLE)
	PropertyGS(GetRadius, SetRadius) float Radius;
	PropertyG(GetWorldRange) Circle Range;
#endif
#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_RECT)
	PropertyGS(GetRect, SetRect) RECT Rect;
	PropertyG(GetWorldRange) RECT Range;
#endif

	PropertyGS(GetIsTrigger, SetIsTrigger) bool IsTrigger;
	PropertyG(GetTag) Tag Tag;
};

