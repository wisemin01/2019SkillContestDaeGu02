#include "DXUT.h"
#include "Bullet.h"

#include "HPModule.h"
#include "Camera.h"

void Bullet::Initialize()
{
	renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("bullet")->Get(0)));
	renderer->Change(UnitStateType::Idle);

	AddComponent<Collider>();
	collider->SetRange(10, 10);
	collider->IsTrigger = true;

	AddComponent<Rigidbody>();
	rigidbody->Friction = 0.92f;
}

void Bullet::Update()
{
	transform->Rotation = m_vDirection.ToRotationValue();

	rigidbody->AddForce(m_vDirection * m_fSpeed * Time::Delta());
}

void Bullet::Release()
{
}

void Bullet::OnCollision(Collider* other)
{
	if (other->IsTrigger == true)
		return;

	if (other->Tag == m_TargetTag)
	{
		Destroy(this->Base);

		HPModule* pHP = other->GetComponent<HPModule>();

		if (pHP)
		{
			pHP->Minus(m_iDamage);
			Camera::MainCamera()->Shake(0.2f, 5.0f);
		}
	}
}

void Bullet::Set(Vector3 direction, float speed, Tag targetTag, int damage)
{
	m_vDirection = direction;
	m_fSpeed = speed;
	m_iDamage = damage;
	m_TargetTag = targetTag;
}
