#pragma once
#include "Component.h"

class Trigger :
	public Component
{
private:

public:
	EventHandler<Collider*> OnTriggerStay;
public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void OnCollision(Collider* other) override;
};

