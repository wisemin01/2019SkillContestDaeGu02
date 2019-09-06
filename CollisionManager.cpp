#include "DXUT.h"
#include "CollisionManager.h"

#include "Collider.h"

void CollisionManager::Register(Collider* collider)
{
	m_listColliders.push_back(collider);
}

void CollisionManager::Unregister(Collider* collider)
{
	m_listColliders.remove(collider);
}

void CollisionManager::Update()
{
	if (m_listColliders.size() < 2)
		return;

	auto End = std::prev(m_listColliders.end());

	for (auto col1 = m_listColliders.begin(); col1 != End; col1++)
	{
		for (auto col2 = std::next(col1); col2 != m_listColliders.end(); col2++)
		{
			// TODO: 충돌 검출

			auto& C1 = *col1;
			auto& C2 = *col2;

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_CIRCLE)
			if (Circle::Intersect(C1->Range, C2->Range))
			{
				C1->Base->OnCollision(C2);
				C2->Base->OnCollision(C1);
			}
#endif

#if (COLLISION_CALCULATE_TYPE & COLLISION_CALCULATETYPE_RECT)
			RECT rc;

			if (IntersectRect(&rc, &C1->Range, &C2->Range))
			{
				C1->Base->OnCollision(C2);
				C2->Base->OnCollision(C1);
			}
#endif

		}
	}
}

void CollisionManager::Reset()
{
	m_listColliders.clear();
}
