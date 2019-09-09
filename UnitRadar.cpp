#include "DXUT.h"
#include "UnitRadar.h"

void UnitRadar::Initialize()
{
	AddComponent<Collider>();
	collider->IsTrigger = true;
}

void UnitRadar::Update()
{
}

void UnitRadar::LateUpdate()
{
}

void UnitRadar::Release()
{
}

void UnitRadar::OnCollision(Collider* other)
{
	OnDetected(other);
}

void UnitRadar::Set(Actor* parent, float width, float height)
{
	transform->SetParent(parent->transform);

	collider->SetRange(width, height);
}
