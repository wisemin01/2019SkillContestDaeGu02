#include "DXUT.h"
#include "LineRenderer.h"

void LineRenderer::Initialize()
{
	Super::m_RenderType = RenderType::UI;
	Super::Initialize();
}

void LineRenderer::Update()
{
	Super::Update();
}

void LineRenderer::Release()
{
	SAFE_DELETE_ARRAY(m_pLineArr);
	Super::Release();
}

void LineRenderer::Render()
{
	if (m_pLineArr)
	{
		RENDER.SetTransformForSprite(&transform->GetWorldMatrix());
		RENDER.DrawLine(m_pLineArr, m_iCount, m_iLineWidth, m_Color);
	}
}

void LineRenderer::Set(Vector2* lineArr, int count, int width, Color color)
{
	SAFE_DELETE_ARRAY(m_pLineArr);

	m_pLineArr		= lineArr;
	m_iCount		= count;
	m_iLineWidth	= width;
	m_Color			= color;
}