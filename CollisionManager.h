#pragma once
#include "Singleton.h"

#define COLLISION_CALCULATETYPE_CIRCLE	(1 << 1)
#define COLLISION_CALCULATETYPE_RECT	(1 << 2)

class Collider;

class CollisionManager :
	public Singleton<CollisionManager>
{
private:
	std::list< Collider* > m_listColliders;
public:
	CollisionManager() {}
	~CollisionManager() { Reset(); }

	void Register(Collider* collider);
	void Unregister(Collider* collider);

	void Update();
	void Reset();
};

#define COLLISION CollisionManager::GetInstance()