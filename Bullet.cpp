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

	m_pDeleteTimer = Timer::Create(3.0f);
}

void Bullet::Update()
{
	transform->Rotation = m_vDirection.ToRotationValue();

	rigidbody->AddForce(m_vDirection * m_fSpeed * Time::Delta());

	if (m_pDeleteTimer->IsEnd)
	{
		Destroy(this->Base);
	}
}

void Bullet::Release()
{
	Timer::Destroy(m_pDeleteTimer);
	m_pDeleteTimer = nullptr;
}

void Bullet::OnCollision(Collider* other)
{
	if (other->IsTrigger == true)
		return;

	if (other->Tag == m_TargetTag)
	{
		Destroy(this->Base);

		if (HPModule * pHP = other->GetComponent<HPModule>(); pHP != nullptr)
		{
			pHP->Minus(m_iDamage);
			Camera::MainCamera()->Shake(0.1f, 3.8f);
		}
	}
}

void Bullet::OnDestroy()
{
	Actor* pEffect = Actor::Create(TagType::Effect, renderer->Layer + 1);

	pEffect->renderer->SetSingleAnimation(Sprite::Find("attack-effect"), 0.03f, true);
	pEffect->transform->Position = transform->Position;
}

void Bullet::Set(Vector3 direction, float speed, Tag targetTag, int damage, float destroyTime)
{
	m_vDirection = direction;
	m_fSpeed = speed;
	m_iDamage = damage;
	m_TargetTag = targetTag;

	m_pDeleteTimer->Reset(destroyTime);
}
