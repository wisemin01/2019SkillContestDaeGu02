#pragma once
#include "Component.h"

class Button :
	public Component
{
private:

	RECT m_rcButtonRange = { 0 };

	bool m_bIsGrowOnMouseCursor = true;

public:

	EventHandler<EmptyEventArg> OnButtonClick;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void SetRange(float width, float height);
	void SetRange();

private:

	RECT GetWorldRange();
};

