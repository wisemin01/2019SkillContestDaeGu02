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
		renderer->CurrentAnime->SetColor(
			Lerp(renderer->CurrentAnime->AnimeColor, m_End, m_fSpeed));
		break;
	}
}

template<typename T>
inline void Fade<T>::Release()
{

}
