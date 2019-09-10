#include "DXUT.h"
#include "Soldier.h"

#include "FSM.h"

#include "SoldierIdle.h"
#include "SoldierMove.h"
#include "SoldierAttack.h"

#include "PlayerController.h"
#include "UnitRadar.h"
#include "HPModule.h"
#include "Camera.h"

void Soldier::Initialize()
{
	Super::Initialize();

	PlayerController::AddUnit();

	HPModule* pHP = AddComponent<HPModule>();
	pHP->OnUnitDeath += CreateListener(EmptyEventArg, OnHpZero);

	rigidbody->PhysicalTreatment = true;
	rigidbody->Friction = 0.5f;

	m_pFSM = AddComponent<FSM<Soldier>>();
	
	m_pFSM->SetOwner(this);
	m_pFSM->AddState(UnitStateType::Idle, new SoldierIdle());
	m_pFSM->AddState(UnitStateType::Move, new SoldierMove());
	m_pFSM->AddState(UnitStateType::Attack, new SoldierAttack());

	m_pFSM->ChangeState(UnitStateType::Idle);
	
	OnRightClick	= CreateListener(Vector3, OnMoveCommand);
	OnSelect		= CreateListener(RECT, OnSelectCommand);
	OnDeselect		= CreateListener(EmptyEventArg, OnDeselectCommand);
	OnStop			= CreateListener(EmptyEventArg, OnStopCommand);

	PlayerController::GetMain()->OnRightClick	+= OnRightClick;
	PlayerController::GetMain()->OnSelect		+= OnSelect;
	PlayerController::GetMain()->OnDeselect		+= OnDeselect;
	PlayerController::GetMain()->OnStop			+= OnStop;

	CreateSelectEffect();
}

void Soldier::Update()
{
	Super::Update();

	if (m_bIsSelect == true)
	{
		Lerp(m_pSelectEffect->transform->Scale, Vector3::One, Time::Delta());
	}

	if (m_pTarget && m_pTarget->IsLive == false)
		m_pTarget = nullptr;
}

void Soldier::LateUpdate()
{
	m_bIsDetectedOnFrame = false;
}

void Soldier::Release()
{
	Super::Release();
	PlayerController::RemoveUnit();
}

void Soldier::OnDestroy()
{
	Super::OnDestroy();

	SoundSource::Load("destroyed(3)", L"Sound/destroyed(3).wav")->DuplicatePlay();

	Actor* pExplosion = Actor::Create(TagType::Effect, 4);
	pExplosion->renderer->SetSingleAnimation(Sprite::Find("explosion-effect-2"), 0.06f, true);
	pExplosion->transform->Position = transform->Position;

	Destroy(m_pSelectEffect);
	Destroy(m_pRadar);

	PlayerController::GetMain()->OnRightClick.Remove(OnRightClick);
	PlayerController::GetMain()->OnSelect.Remove(OnSelect);
	PlayerController::GetMain()->OnDeselect.Remove(OnDeselect);
	PlayerController::GetMain()->OnStop.Remove(OnStop);
}

void Soldier::OnHpZero(EmptyEventArg e)
{
	Destroy(this->Base);
}

void Soldier::OnMoveCommand(Vector3 v)
{
	if (m_bIsSelect == false)
		return;

	m_vEndPosition = v;

	m_pFSM->ChangeState(UnitStateType::Move);
}

void Soldier::OnSelectCommand(RECT rc)
{
	m_bIsSelect = IntersectRect(&rc, &collider->GetWorldRange());

	m_pSelectEffect->IsVisible = m_bIsSelect;
}

void Soldier::OnDeselectCommand(EmptyEventArg e)
{
	m_bIsSelect = false;
	m_pSelectEffect->IsVisible = m_bIsSelect;
}

void Soldier::OnStopCommand(EmptyEventArg e)
{
	m_vEndPosition = transform->Position;
}

void Soldier::OnRadarDetected(Collider* other)
{
	if (other->Tag == TagType::Enemy) 
	{
		m_bIsDetectedOnFrame = true;

		if (m_pTarget == nullptr) 
		{
			m_pTarget = other->Base;
			return;
		}

		Vector3 ot1 = other->transform->Position;
		Vector3 ot2 = m_pTarget->transform->Position;
		Vector3 v = transform->Position;
		
		float ot1_length = Vector3::Length(v - ot1);
		float ot2_length = Vector3::Length(v - ot2);

		if (ot1_length < ot2_length)
			m_pTarget = other->Base;
	}
}

void Soldier::CreateSelectEffect()
{
	m_pSelectEffect = ACTOR.Create(TagType::Effect, renderer->Layer + 1);

	m_pSelectEffect->renderer->AddAnimation(0, new Animation(Sprite::Find("select-effect"), 0.05f));
	m_pSelectEffect->renderer->Change(0);
	m_pSelectEffect->SetParent(this->Base);

	m_pSelectEffect->IsVisible = false;
}

void Soldier::CreateRadar(float width, float height)
{
	m_pRadar = ACTOR.Create(TagType::Radar);

	auto com = m_pRadar->AddComponent<UnitRadar>();

	com->Set(this->Base, width, height);
	com->OnDetected += CreateListener(Collider*, OnRadarDetected);
}
