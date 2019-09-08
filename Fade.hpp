#include "Fade.h"
#pragma once


template<typename T>
inline void Fade<T>::Set(const T& end, int fadeTarget, float speed)
{
	m_End = end;
	m_iType = fadeTarget;
	m_fSpeed = speed;
}

template<typename T>
inline void Fade<T>::Initialize()
{

}

template<typename T>
inline void Fade<T>::Update()
{
	switch (m_iType)
	{
	case FadeTarget::Renderer_Alpha:
		//renderer->CurrentAnime->SetColor(
		//	Lerp(renderer->CurrentAnime->AnimeColor, m_End, m_fSpeed * Time::Delta()));

		renderer->CurrentAnime->SetAlpha(renderer->CurrentAnime->GetAlpha() + m_fSpeed * Time::Delta());

		if (renderer->CurrentAnime->GetAlpha() >= 1.0f)
			renderer->CurrentAnime->SetAlpha(1.0f);

		if (renderer->CurrentAnime->GetAlpha() <= 0.0f)
			renderer->CurrentAnime->SetAlpha(0.0f);
		break;
	}
}

template<typename T>
inline void Fade<T>::Release()
{

}
