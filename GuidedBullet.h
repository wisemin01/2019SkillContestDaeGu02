#pragma once
#include "Component.h"

class GuidedBullet :
	public Component
{
private:

	float	m_fSpeed = 0.0f;
	int		m_iDamage = 1.0f;
	Actor*	m_pTarget = nullptr;
	Tag		m_TargetTag = TagType::None;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void OnCollision(Collider* other) override;

	void Set(Actor* target, float speed, Tag targetTag, int damage);
};

