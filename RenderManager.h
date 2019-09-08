#pragma once
#include "Singleton.h"

using TransformStateType = D3DTRANSFORMSTATETYPE;

class Renderer;
class Font;

class RenderManager :
	public Singleton<RenderManager>
{
private:
	ID3DXSprite* m_pSprite = nullptr;

	std::list<Renderer*> m_listRenderers;
	std::list<Renderer*> m_listUIRenderers;

	LPD3DXLINE m_pLine = nullptr;

public:
	RenderManager();
	~RenderManager();

	void Register(Renderer* renderer);
	void Unregister(Renderer* renderer);

	// Draw All Objects
	void Render();

	void Sort();

	void SetTransformForSprite(const Matrix* m);
	void SetTransformForDevice(TransformStateType state, const Matrix* m);

	void Draw(Sprite* texture, Color color = Color::White);
	void Draw(Font* font, const string& context, Color color = Color::White);
	void Draw(Font* font, const wstring& context, Color color = Color::White);
	void CenterDraw(Sprite* texture, Color color = Color::White);

	void DrawLine(const Vector2* lines, int count, int size, Color color = Color::White);

	void Reset();

public:
	void OnLostDevice();
	void OnResetDevice();
};

#define RENDER RenderManager::GetInstance()