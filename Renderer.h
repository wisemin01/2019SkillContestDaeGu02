#pragma once
#include "Component.h"

static class RenderType
{
public:
	enum
	{
		None = -1,
		ObjectSpace,
		UI
	};

};

class Animation;

class Renderer :
	public Component
{
protected:
	std::map< int, Animation* > m_mapAnimations;

	Animation* m_pCurrentAnime = nullptr;

	int m_RenderType = RenderType::ObjectSpace;
	int m_iRenderLayer = 0;

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

	// change current animation's sprite
	void ChangeSprite(Sprite* sprite);

	int GetLayer() const { return m_iRenderLayer; }
	void SetLayer(int value) { m_iRenderLayer = value; }

	void SetSingleAnimation(Sprite* sprite, float delay = 0.0f, bool isDestroyOnFrameEnd = false);

public:

	Animation* GetCurrentAnimation() { return m_pCurrentAnime; }

	int GetRenderType() { return m_RenderType; }

	// argument optional : RenderType::enum
	void SetRenderType(int renderType);

	PropertyGS(GetRenderType, SetRenderType) int RenderType;
	PropertyGS(GetLayer, SetLayer) int Layer;
	PropertyG(GetCurrentAnimation) Animation* CurrentAnime;
};

