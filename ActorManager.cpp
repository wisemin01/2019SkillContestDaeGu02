#include "DXUT.h"
#include "ActorManager.h"

#include "Actor.h"
#include "Transform.h"


#define COMPONENTTYPE_TRANSFORM (1 << 1)
#define COMPONENTTYPE_RENDERER  (1 << 2)

// TODO: Setting default component modules.
#define DEFAULT_COMPONENT	COMPONENTTYPE_TRANSFORM | COMPONENTTYPE_RENDERER


Actor* ActorManager::Create(Tag tag, bool isVisible, bool isActive, int layer)
{
	Actor* A = new Actor(tag, isVisible, isActive);

#if (DEFAULT_COMPONENT & COMPONENTTYPE_TRANSFORM)
	A->AddComponent<Transform>();
#endif

#if (DEFAULT_COMPONENT & COMPONENTTYPE_RENDERER)
	A->AddComponent<Renderer>();
	A->renderer->Layer = layer;
#endif

	m_listActors.push_back(A);

	return A;
}

Actor* ActorManager::Create(Tag tag, int layer)
{
	Actor* A = new Actor(tag);

#if (DEFAULT_COMPONENT & COMPONENTTYPE_TRANSFORM)
	A->AddComponent<Transform>();
#endif

#if (DEFAULT_COMPONENT & COMPONENTTYPE_RENDERER)
	A->AddComponent<Renderer>();
	A->renderer->Layer = layer;
#endif

	m_listActors.push_back(A);

	return A;
}

Actor* ActorManager::CreateEmpty(Tag tag, bool isVisible, bool isActive)
{
	Actor* A = new Actor(tag, isVisible, isActive);

	m_listActors.push_back(A);

	return A;
}

Actor* ActorManager::FindActor(Tag tag)
{
	for (auto iter : m_listActors)
	{
		if (iter->m_Tag == tag)
			return iter;
	}
}

void ActorManager::Update()
{
	for (auto iter : m_listActors)
	{
		if (iter->IsLive == true)
		{
			if (iter->IsActive)
			{
				iter->Update();
			}
		}
	}

	for (auto iter = m_listActors.begin(); iter != m_listActors.end();)
	{
		Actor* actor = *iter;

		if (actor->IsLive == true)
		{
			if (actor->IsActive)
			{
				actor->LateUpdate();
			}

			iter++;
		}
		else
		{
			actor->Release();
			SAFE_DELETE(actor);

			iter = m_listActors.erase(iter);
		}
	}
}

void ActorManager::Reset()
{
	for(auto iter : m_listActors)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}

	m_listActors.clear();
}
