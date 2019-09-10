#pragma once
#include "Component.h"

class Bullet :
	public Component
{
private:

	float	m_fSpeed		= 0.0f;
	int		m_iDamage		= 1.0f;
	Vector3 m_vDirection	= Vector3::Zero;
	Tag		m_TargetTag		= TagType::None;

	Timer*	m_pDeleteTimer	= nullptr;

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void OnCollision(Collider* other) override;

	virtual void OnDestroy() override;

	void Set(Vector3 direction, float speed, Tag targetTag, int damage, float destroyTime = 3.0f);
};

