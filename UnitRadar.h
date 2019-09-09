#pragma once
#include "Component.h"

class UnitRadar :
	public Component
{
private:

public:
	EventHandler<Collider*> OnDetected;
public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

	virtual void OnCollision(Collider* other) override;

	void Set(Actor* parent, float width, float height);
};

