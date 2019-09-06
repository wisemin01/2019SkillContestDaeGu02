#pragma once

class Font
{
	friend class ResourceManager;
	friend class RenderManager;
private:
	LPD3DXFONT m_pFont = nullptr;

public:
	~Font() { SAFE_RELEASE(m_pFont); }

	static Font* Load(const string& fontKey, int size);
	static Font* Find(const string& fontKey, int size);
};

