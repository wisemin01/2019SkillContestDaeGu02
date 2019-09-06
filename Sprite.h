#pragma once

class Sprite
{
private:

	IDirect3DTexture9*	m_pTexture;
	D3DXIMAGE_INFO		m_tInfo;

public:
	Sprite() : m_pTexture(nullptr), m_tInfo() {}
	virtual ~Sprite();

	virtual void	Load(const std::string& path, int count = 0);
	virtual Sprite* Get(int count = -1);
	virtual int		Size();

	int GetWidthSize() { return m_tInfo.Width; }
	int GetHeightSize() { return m_tInfo.Height; }

	inline IDirect3DTexture9* GetTexture() { return m_pTexture; }

public:
	PropertyG(GetTexture)		IDirect3DTexture9* Tex;
	PropertyG(GetWidthSize)		int Width;
	PropertyG(GetHeightSize)	int Height;

public:

	static Sprite* Find(const string& key);
	static Sprite* Load(const string& key, const string& path, int count = 0);
};

