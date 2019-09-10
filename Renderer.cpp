#include "DXUT.h"
#include "Renderer.h"

#include "Actor.h"
#include "Animation.h"
#include "SingleAnimation.h"

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

void Renderer::ChangeSprite(Sprite* sprite)
{
	if (CurrentAnime)
	{
		CurrentAnime->AnimeSprite = sprite;
	}
}

void Renderer::SetSingleAnimation(Sprite* sprite, float delay, bool isDestroyOnFrameEnd)
{
	if (auto find = m_mapAnimations.find(0); find != m_mapAnimations.end()) 
	{
		throw std::exception("Animation is already assigned to position 0.");
	}

	AddAnimation(0, new Animation(sprite, delay));
	Change(0);

	if (isDestroyOnFrameEnd)
	{
		AddComponent<SingleAnimation>();
	}
}

void Renderer::SetRenderType(int renderType)
{
	// 변경 사항이 없을 경우
	if (renderType == m_RenderType)
	{
		return;
	}

	// 변경 사항이 있을경우

	RENDER.Unregister(this);
	m_RenderType = renderType;
	RENDER.Register(this);
}
