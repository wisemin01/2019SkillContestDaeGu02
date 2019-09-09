#include "DXUT.h"
#include "Enemy.h"

#include "FSM.h"
#include "UnitRadar.h"

#include "EnemyIdle.h"
#include "EnemyMove.h"
#include "EnemyAttack.h"
#include "HPModule.h"
#include "Camera.h"
#include "EnemyController.h"

void Enemy::Initialize()
{
	EnemyController::AddUnit();

	AddComponent<Rigidbody>();
	AddComponent<Collider>();

	HPModule* pHP = AddComponent<HPModule>();
	pHP->Set(100);
	pHP->OnUnitDeath += CreateListener(EmptyEventArg, OnHpZero);

	rigidbody->PhysicalTreatment = true;
	rigidbody->Friction = 0.5f;

	collider->SetRange(100, 100);

	renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Test-E")->Get(1)));
	renderer->AddAnimation(UnitStateType::Move, new Animation(Sprite::Find("Test-E")->Get(1)));
	renderer->AddAnimation(UnitStateType::Attack, new Animation(Sprite::Find("Test-E")->Get(1)));

	renderer->Change(UnitStateType::Idle);

	m_pFSM = AddComponent<FSM<Enemy>>();
	m_pFSM->SetOwner(this);

	m_pFSM->AddState(UnitStateType::Idle, new EnemyIdle());
	m_pFSM->AddState(UnitStateType::Move, new EnemyMove());
	m_pFSM->AddState(UnitStateType::Attack, new EnemyAttack());

	m_pFSM->ChangeState(UnitStateType::Idle);

	CreateMoveRadar(800, 800);
	CreateAttackRadar(650, 650);
}

void Enemy::Update()
{
	if (m_pTarget && m_pTarget->IsLive == false)
		m_pTarget = nullptr;
}

void Enemy::LateUpdate()
{
	m_bIsDetectedOnFrame_Move = false;
	m_bIsDetectedOnFrame_Attack = false;
}

void Enemy::Release()
{
	EnemyController::RemoveUnit();
}

void Enemy::OnDestroy()
{
	Camera::MainCamera()->SetShakePower(17.0f);
	Camera::MainCamera()->Shake(0.3f);

	Destroy(m_pAttackRadar);
	Destroy(m_pMoveRadar);
}

void Enemy::OnRadarDetected_Move(Collider* other)
{
	if (other->IsTrigger == true)
		return;

	if (other->Tag == TagType::Player)
	{
		m_bIsDetectedOnFrame_Move = true;

		if (m_pTarget == nullptr)
			m_pTarget = other->Base;
	}
}

void Enemy::OnRadarDetected_Attack(Collider* other)
{
	if (other->IsTrigger == true)
		return;

	if (other->Tag == TagType::Player)
	{
		m_bIsDetectedOnFrame_Attack = true;

		if (m_pTarget == nullptr)
			m_pTarget = other->Base;

		if (m_pTarget != nullptr)
		{
			Vector3 ot1 = m_pTarget->transform->Position;
			Vector3 ot2 = other->transform->Position;
			Vector3 v2 = transform->Position;

			float length1 = Vector3::Length(ot1 - v2);
			float length2 = Vector3::Length(ot2 - v2);

			if (length2 < length1)
				m_pTarget = other->Base;
		}
	}
}

void Enemy::OnHpZero(EmptyEventArg e)
{
	Destroy(this->Base);
}

void Enemy::CreateMoveRadar(float width, float height)
{
	Actor* pRadar = ACTOR.Create(TagType::Radar);

	auto com = pRadar->AddComponent<UnitRadar>();

	com->Set(this->Base, width, height);
	com->OnDetected += CreateListener(Collider*, OnRadarDetected_Move);
}

void Enemy::CreateAttackRadar(float width, float height)
{
	Actor* pRadar = ACTOR.Create(TagType::Radar);

	auto com = pRadar->AddComponent<UnitRadar>();

	com->Set(this->Base, width, height);
	com->OnDetected += CreateListener(Collider*, OnRadarDetected_Attack);
}