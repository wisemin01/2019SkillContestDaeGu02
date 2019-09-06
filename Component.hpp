#pragma once

#include "Actor.h"

template<class COM>
inline COM* Component::AddComponent()
{
	return m_pBaseActor->AddComponent<COM>();
}

template<class COM>
inline COM* Component::GetComponent()
{
	return m_pBaseActor->GetComponent<COM>();
}
