#include "DXUT.h"
#include "ResourceManager.h"

#include "../Optional/SDKsound.h"

#include "Sprite.h"
#include "MultiSprite.h"
#include "SoundSource.h"
#include "Font.h"

#pragma comment(lib, "dsound.lib")

ResourceManager::ResourceManager()
{
	m_pSoundManager = new CSoundManager();

	m_pSoundManager->Initialize(DXUTGetHWND(), 2);
	m_pSoundManager->SetPrimaryBufferFormat(2, 22050, 16);
}

ResourceManager::~ResourceManager()
{
	Clear();

	SAFE_DELETE(m_pSoundManager);
}

Sprite* ResourceManager::InsertSprite(const std::string& key, const std::string& path, int count)
{
	auto find = m_mapSprites.find(key);

	if (find != m_mapSprites.end())
		return find->second;

	Sprite* Spr = ( count == 0 ) ? new Sprite() : new MultiSprite();

	Spr->Load( "./Resource/" + path, count );
	Log(path);

	m_mapSprites.insert( std::make_pair( key, Spr ) );

	return Spr;
}

Sprite* ResourceManager::FindSprite(const string& key)
{
	if (auto find = m_mapSprites.find(key); find != m_mapSprites.end())
	{
		return find->second;
	}

	return nullptr;
}

SoundSource* ResourceManager::InsertSound(const std::string& key, const std::wstring& path)
{
	auto find = m_mapSounds.find(key);

	if (find != m_mapSounds.end())
		return find->second;

	SoundSource* soundSource = new SoundSource();
	
	soundSource->Load(L"./Resource/" + path);

	m_mapSounds.insert(std::make_pair(key, soundSource));

	return soundSource;
}

SoundSource* ResourceManager::FindSound(const std::string& key)
{
	if (auto find = m_mapSounds.find(key); find != m_mapSounds.end())
	{
		return find->second;
	}

	return nullptr;
}

Font* ResourceManager::InsertFont(const std::string& fontKey, int fontSize)
{
	string key = fontKey + std::to_string(fontSize);

	if (auto find = m_mapFonts.find(key); find == m_mapFonts.end()) {

		Font* font = new Font();

		D3DXCreateFontA(g_pDevice, fontSize, 0, FW_HEAVY, 0,
			false, HANGUL_CHARSET, 0, 0, 0, fontKey.c_str(), &font->m_pFont);

		m_mapFonts.insert(std::make_pair(key, font));

		return font;
	}
	else
	{
		return find->second;
	}
}

Font* ResourceManager::FindFont(const std::string& fontKey, int fontSize)
{
	string key = fontKey + std::to_string(fontSize);

	if (auto find = m_mapFonts.find(key); find != m_mapFonts.end())
	{
		return find->second;
	}

	return nullptr;
}

void ResourceManager::Clear()
{
	for (auto iter : m_mapSprites)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapSprites.clear();

	for (auto iter : m_mapSounds)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapSounds.clear();

	for (auto iter : m_mapFonts)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapFonts.clear();
}
