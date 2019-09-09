#include "DXUT.h"
#include "GuidedBullet.h"
#include "HPModule.h"

void GuidedBullet::Initialize()
{
	renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("bullet")->Get(0)));
	renderer->Change(UnitStateType::Idle);

	AddComponent<Collider>();
	collider->SetRange(10, 10);
	collider->IsTrigger = true;

	AddComponent<Rigidbody>();
	rigidbody->Friction = 0.92f;
}

void GuidedBullet::Update()
{
	if (m_pTarget == nullptr)
	{
		Destroy(Base);
		return;
	}

	if (m_pTarget->IsLive == false)
	{
		m_pTarget = nullptr;
		return;
	}

	Vector3 Direction = m_pTarget->transform->Position - transform->Position;

	Direction.Normalize();

	transform->Rotation = Direction.ToRotationValue();

	rigidbody->AddForce(Direction * m_fSpeed * Time::Delta());
}

void GuidedBullet::Release()
{
}

void GuidedBullet::OnCollision(Collider* other)
{
	if (other->Tag == m_TargetTag)
	{
		Destroy(Base);

		HPModule* pHP = other->GetComponent<HPModule>();

		if (pHP)
		{
			pHP->Minus(m_iDamage);
		}
	}
}

void GuidedBullet::Set(Actor* target, float speed, Tag targetTag, int damage)
{
	m_pTarget = target;
	m_fSpeed = speed;
	m_iDamage = damage;
	m_TargetTag = targetTag;
}
