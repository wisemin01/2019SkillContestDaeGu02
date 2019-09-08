#include "DXUT.h"
#include "Soldier.h"

#include "FSM.h"

#include "SoldierIdle.h"
#include "SoldierMove.h"

#include "PlayerController.h"

void Soldier::Initialize()
{
	AddComponent<Rigidbody>();
	AddComponent<Collider>();

	rigidbody->PhysicalTreatment = true;
	rigidbody->Friction = 0.5f;

	collider->SetRange(100, 100);

	renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Test")->Get(1)));
	renderer->AddAnimation(UnitStateType::Move, new Animation(Sprite::Find("Test")->Get(1)));

	m_pFSM = AddComponent<FSM<Soldier>>();
	
	m_pFSM->SetOwner(this);
	m_pFSM->AddState(UnitStateType::Idle, new SoldierIdle());
	m_pFSM->AddState(UnitStateType::Move, new SoldierMove());

	m_pFSM->ChangeState(UnitStateType::Idle);
	
	OnRightClick	= CreateListener(Vector3, OnMoveCommand);
	OnSelect		= CreateListener(RECT, OnSelectCommand);
	OnDeselect		= CreateListener(EmptyEventArg, OnDeselectCommand);
	OnStop			= CreateListener(EmptyEventArg, OnStopCommand);

	MainPlayerController->OnRightClick	+= OnRightClick;
	MainPlayerController->OnSelect		+= OnSelect;
	MainPlayerController->OnDeselect	+= OnDeselect;
	MainPlayerController->OnStop		+= OnStop;

	CreateSelectEffect();
}

void Soldier::Update()
{
}

void Soldier::Release()
{
	
}

void Soldier::OnDestroy()
{
	MainPlayerController->OnRightClick	.Remove(OnRightClick);
	MainPlayerController->OnSelect		.Remove(OnSelect);
	MainPlayerController->OnDeselect	.Remove(OnDeselect);
	MainPlayerController->OnStop		.Remove(OnStop);
}

void Soldier::OnCollision(Collider* other)
{
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

void Soldier::CreateSelectEffect()
{
	m_pSelectEffect = ACTOR.Create(TagType::Effect, renderer->Layer + 1);

	m_pSelectEffect->renderer->AddAnimation(0, new Animation(Sprite::Find("select-effect"), 0.05f));
	m_pSelectEffect->renderer->Change(0);
	m_pSelectEffect->SetParent(this->Base);

	m_pSelectEffect->IsVisible = false;
}
