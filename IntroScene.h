#pragma once
#include "Scene.h"

class IntroScene :
	public Scene
{
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

