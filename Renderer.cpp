#include "DXUT.h"
#include "Renderer.h"

#include "Actor.h"
#include "Animation.h"

void Renderer::Initialize()
{
	Base->renderer = this;

	RENDER.Register(this);
}

void Renderer::Update()
{
	if (m_pCurrentAnime)
	{
		m_pCurrentAnime->Update();
	}
}

void Renderer::Release()
{
	if (Base->renderer == this)
		Base->renderer = nullptr;

	RENDER.Unregister(this);

	for (auto iter : m_mapAnimations)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapAnimations.clear();
}

void Renderer::Render()
{
	if (m_pCurrentAnime)
	{

		RENDER.SetTransformForSprite(&transform->GetWorldMatrix());
		m_pCurrentAnime->Render();

	}
}

void Renderer::AddAnimation(int key, Animation* animation)
{
	if (auto find = m_mapAnimations.find(key); find == m_mapAnimations.end())
	{
		m_mapAnimations.insert(std::make_pair(key, animation));
	}
}

void Renderer::Change(int key)
{
	if (auto find = m_mapAnimations.find(key); find != m_mapAnimations.end())
	{
		m_pCurrentAnime = find->second;
		return;
	}

	throw exception("FSM<OWNER>::ChangeState(int key) - Invalid key value.");
}

void Renderer::SetRenderType(int renderType)
{
	// ���� ������ ���� ���
	if (renderType == m_RenderType)
	{
		return;
	}

	// ���� ������ �������

	RENDER.Unregister(this);
	m_RenderType = renderType;
	RENDER.Register(this);
}
