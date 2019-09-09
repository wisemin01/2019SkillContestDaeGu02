#include "DXUT.h"
#include "Component.h"

#include "Actor.h"

void Component::Destroy(Actor* target)
{
	if (target != nullptr) 
	{
		target->IsLive = false;
	}
}

Transform* Component::GetTransform() const
{
	return Base->transform;
}

Renderer* Component::GetRenderer() const
{
	return Base->renderer;
}

Collider* Component::GetCollider() const
{
	return Base->collider;
}

Rigidbody* Component::GetRigidbody() const
{
	return Base->rigidbody;
}
