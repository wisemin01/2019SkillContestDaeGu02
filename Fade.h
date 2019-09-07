#pragma once
#include "Component.h"

template <typename T>
class Fade :
	public Component
{
private:

	T* m_pTarget = nullptr;
	T m_End;

	float m_fSpeed = 0.0f;

	int m_iType = FadeTarget::None;

public:

	void Set(const T& end, int fadeTarget = FadeTarget::Renderer_Alpha, float speed = 0.1f);

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};

#include "Fade.hpp"
