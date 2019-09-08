#include "DXUT.h"
#include "SoundSource.h"

#include "../Optional/SDKsound.h"
#include "../Optional/SDKwavefile.h"

#include <assert.h>

#pragma comment(lib, "dsound.lib")

SoundSource::~SoundSource()
{
	SAFE_DELETE(m_pSoundSource);
}

void SoundSource::Load(const std::wstring& path)
{
	RESOURCE.GetSoundManager()->Create(&m_pSoundSource, (LPWSTR)path.c_str());
}

void SoundSource::Play(bool isLoop, int volume)
{
	assert(volume <= 100 && volume >= 0);

	// m_pSoundSource->GetBuffer(0)->SetVolume((volume - 100) * 100);
	m_pSoundSource->Play(0, isLoop);
}

void SoundSource::DuplicatePlay(bool isLoop, int volume)
{
	assert(volume <= 100 && volume >= 0);

	LPDIRECTSOUNDBUFFER lpDS;

	RESOURCE.GetSoundManager()->GetDirectSound()->DuplicateSoundBuffer(m_pSoundSource->GetBuffer(0), &lpDS);

	lpDS->SetCurrentPosition(0);
	// lpDS->SetVolume((volume - 100) * 100);
	lpDS->Play(0, 0, isLoop);
}

void SoundSource::Stop()
{
	m_pSoundSource->Stop();
}

SoundSource* SoundSource::Find(const string& key)
{
	return RESOURCE.FindSound(key);
}

SoundSource* SoundSource::Load(const string& key, const wstring& path)
{
	return RESOURCE.InsertSound(key, path);
}
