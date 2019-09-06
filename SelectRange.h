#pragma once
#include "Component.h"

class LineRenderer;

class SelectRange :
	public Component
{
private:
	Vector3 m_vStart	= Vector3::Zero;
	Vector3 m_vEnd		= Vector3::Zero;

	LineRenderer* m_pLineRenderer = nullptr;

public:
	EventHandler<RECT> OnSelect;
public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

};

