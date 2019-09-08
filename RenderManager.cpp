#include "DXUT.h"
#include "RenderManager.h"

#include "Renderer.h"
#include "Sprite.h"
#include "Font.h"

RenderManager::RenderManager()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	D3DXCreateLine(g_pDevice, &m_pLine);
}

RenderManager::~RenderManager()
{
	Reset();

	SAFE_RELEASE(m_pLine);
	SAFE_RELEASE(m_pSprite);
}

void RenderManager::Register(Renderer* renderer)
{
	if (renderer->GetRenderType() == RenderType::ObjectSpace)
	{
		m_listRenderers.push_back(renderer);
	}

	if (renderer->GetRenderType() == RenderType::UI)
	{
		m_listUIRenderers.push_back(renderer);
	}
}

void RenderManager::Unregister(Renderer* renderer)
{
	if (renderer->GetRenderType() == RenderType::ObjectSpace)
	{
		m_listRenderers.remove(renderer);
	}

	if (renderer->GetRenderType() == RenderType::UI)
	{
		m_listUIRenderers.remove(renderer);
	}
}

void RenderManager::Render()
{
	// RENDER OBJECTSPACE
	{
		m_pSprite->Begin(D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_ALPHABLEND);

		// TODO: RENDER

		for (auto iter : m_listRenderers)
		{
			if (iter->Base->IsVisible)
				iter->Render();
		}

		m_pSprite->End();
	}

	// RENDER UI ( NONE OBJECTSPACE ) 
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		// TODO: RENDER

		for (auto iter : m_listUIRenderers)
		{
			if (iter->Base->IsVisible)
				iter->Render();
		}

		m_pSprite->End();
	}
}

void RenderManager::Sort()
{
	m_listRenderers.sort([&](const Renderer* left, const Renderer* right) 
		{
			if (left->Layer < right->Layer)
				return true;

			if (left->Layer == right->Layer)
			{
				return left->transform->Position.y < right->transform->Position.y;
			}

			return false;
		}
	);

	m_listUIRenderers.sort([&](Renderer* left, Renderer* right) 
		{
			if (left->Layer < right->Layer)
				return true;

			return false;
		}
	);
}

void RenderManager::SetTransformForSprite(const Matrix* m)
{
	m_pSprite->SetTransform(m);
}

void RenderManager::SetTransformForDevice(TransformStateType state, const Matrix* m)
{
	g_pDevice->SetTransform(state, m);
}

void RenderManager::Draw(Sprite* texture, Color color)
{
	if (auto tex = texture->Tex; tex == nullptr) 
	{
		return;
	}
	else
	{
		m_pSprite->Draw(tex, NULL, NULL, NULL, color);
	}
}

void RenderManager::Draw(Font* font, const string& context, Color color)
{
	if (font == nullptr)
		return;

	font->m_pFont->DrawTextA(m_pSprite, context.c_str(),
		context.size(), nullptr, DT_NOCLIP, color);
}

void RenderManager::Draw(Font* font, const wstring& context, Color color)
{
	if (font == nullptr)
		return;

	font->m_pFont->DrawTextW(m_pSprite, context.c_str(),
		context.size(), nullptr, DT_NOCLIP, color);
}


void RenderManager::CenterDraw(Sprite* texture, Color color)
{
	if (auto tex = texture->Tex; tex == nullptr)
	{
		return;
	}
	else
	{
		Vector3 center = Vector3(texture->Width / 2.f, texture->Height / 2.f, 0);

		m_pSprite->Draw(tex, NULL, &center, NULL, color);
	}
}

void RenderManager::DrawLine(const Vector2* lines, int count, int size, Color color)
{
	m_pSprite->SetTransform(&Matrix::IdentityCoord);

	m_pLine->SetWidth(size);
	m_pLine->Draw(lines, count, color);
}

void RenderManager::Reset()
{
	m_listRenderers.clear();
	m_listUIRenderers.clear();
}

void RenderManager::OnLostDevice()
{
	m_pSprite->OnLostDevice();
}

void RenderManager::OnResetDevice()
{
	m_pSprite->OnResetDevice();
}
