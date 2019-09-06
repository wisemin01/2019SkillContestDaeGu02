#pragma once
#include "Component.h"

static class RenderType
{
public:
	enum
	{
		None = -1,
		Rendering_ObjectSpace,
		Rendering_UI
	};

};

class Animation;

class Renderer :
	public Component
{
protected:
	std::map< int, Animation* > m_mapAnimations;

	Animation* m_pCurrentAnime = nullptr;

	int m_RenderType = RenderType::Rendering_ObjectSpace;
public:
	Renderer() {}
	virtual ~Renderer() {}

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render();

	void AddAnimation(int key, Animation* animation);
	void Change(int key);

public:

	Animation* GetCurrentAnimation() { return m_pCurrentAnime; }

	int GetRenderType() { return m_RenderType; }

	// argument optional : RenderType::enum
	void SetRenderType(int renderType);

	PropertyGS(GetRenderType, SetRenderType) int RenderType;
	PropertyG(GetCurrentAnimation) Animation* CurrentAnime;
};

