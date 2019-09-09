#include "DXUT.h"
#include "Trigger.h"

void Trigger::Initialize()
{
	AddComponent<Collider>();
	collider->IsTrigger = true;
}

void Trigger::Update()
{
}

void Trigger::Release()
{
}

void Trigger::OnCollision(Collider* other)
{
	OnTriggerStay(other);
}
