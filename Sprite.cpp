#include "DXUT.h"
#include "Sprite.h"

Sprite::~Sprite()
{
	SAFE_RELEASE(m_pTexture);
}

void Sprite::Load(const std::string& path, int count)
{
	D3DXCreateTextureFromFileExA(g_pDevice, path.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
		D3DX_DEFAULT, D3DX_DEFAULT, 
		D3DCOLOR_XRGB(10, 10, 10), &m_tInfo,
		NULL, &m_pTexture);
}

Sprite* Sprite::Get(int count)
{
	return this;
}

int Sprite::Size()
{
	return 1;
}

Sprite* Sprite::Find(const string& key)
{
	return RESOURCE.FindSprite(key);
}

Sprite* Sprite::Load(const string& key, const string& path, int count)
{
	return RESOURCE.InsertSprite(key, path, count);
}
