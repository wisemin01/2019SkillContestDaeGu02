#include "DXUT.h"
#include "TextRenderer.h"

#include "Font.h"

void TextRenderer::Initialize()
{
	Super::m_RenderType = RenderType::Rendering_UI;
	Super::Initialize();
}

void TextRenderer::Update()
{
	Super::Update();
}

void TextRenderer::Release()
{
	Super::Release();
}

void TextRenderer::Render()
{
	RENDER.SetTransformForSprite(&transform->GetWorldMatrix());
	RENDER.Draw(m_pFont, m_sContext, m_Color);
}

void TextRenderer::Set(const string& fontKey, int fontSize, const OutputString& context, Color color)
{
	m_pFont		= Font::Load(fontKey, fontSize);
	m_sContext	= context;
	m_Color		= color;
}

void TextRenderer::SetContext(const OutputString& context)
{
	m_sContext = context;
}
