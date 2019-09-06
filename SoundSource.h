#pragma once

class CSound;

class SoundSource
{
private:
	CSound* m_pSoundSource = nullptr;

public:
	SoundSource() {}
	~SoundSource();

	virtual void Load(const std::wstring& path);

	void Play(bool isLoop = false, int volume = 100);
	void DuplicatePlay(bool isLoop = false, int volume = 100);

public:

	static SoundSource* Find(const string& key);
	static SoundSource* Load(const string& key, const wstring& path);
};

