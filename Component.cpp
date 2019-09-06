#include "DXUT.h"
#include "Component.h"

#include "Actor.h"

void Component::Destroy(Actor* target)
{
	target->IsLive = false;
}

Transform* Component::GetTransform()
{
	return Base->transform;
}

Renderer* Component::GetRenderer()
{
	return Base->renderer;
}

Collider* Component::GetCollider()
{
	return Base->collider;
}

Rigidbody* Component::GetRigidbody()
{
	return Base->rigidbody;
}
