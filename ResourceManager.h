#pragma once
#include "Singleton.h"

class Sprite;
class Font;
class SoundSource;
class CSoundManager;

class ResourceManager final :
	public Singleton<ResourceManager>
{
private:
	std::map< std::string, Sprite* > m_mapSprites;
	std::map< std::string, SoundSource* > m_mapSounds;
	std::map< std::string, Font* > m_mapFonts;

	CSoundManager* m_pSoundManager = nullptr;
public:
	ResourceManager();
	~ResourceManager();

	Sprite* InsertSprite(const std::string& key, const std::string& path, int count = 0);
	Sprite* FindSprite(const std::string& key);

	SoundSource* InsertSound(const std::string& key, const std::wstring& path);
	SoundSource* FindSound(const std::string& key);

	Font* InsertFont(const std::string& fontKey, int fontSize);
	Font* FindFont(const std::string& fontKey, int fontSize);

	CSoundManager* GetSoundManager() { return m_pSoundManager; }

	void Clear();
};

#define RESOURCE ResourceManager::GetInstance()