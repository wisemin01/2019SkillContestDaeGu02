#include "DXUT.h"
#include "SoundSource.h"

#include "../Optional/SDKsound.h"
#include "../Optional/SDKwavefile.h"

#pragma comment(lib, "dsound.lib")

SoundSource::~SoundSource()
{
	SAFE_DELETE(m_pSoundSource);
}

void SoundSource::Load(const std::wstring& path)
{
	RESOURCE.GetSoundManager()->Create(&m_pSoundSource, (LPWSTR)path.c_str());
}

void SoundSource::Play(bool isLoop)
{
	m_pSoundSource->Play(0, isLoop);
}

void SoundSource::DuplicatePlay(bool isLoop)
{
	LPDIRECTSOUNDBUFFER lpDS;

	RESOURCE.GetSoundManager()->GetDirectSound()->DuplicateSoundBuffer(m_pSoundSource->GetBuffer(0), &lpDS);

	lpDS->SetCurrentPosition(0);
	lpDS->Play(0, 0, isLoop);
}

SoundSource* SoundSource::Find(const string& key)
{
	return RESOURCE.FindSound(key);
}

SoundSource* SoundSource::Load(const string& key, const wstring& path)
{
	return RESOURCE.InsertSound(key, path);
}
