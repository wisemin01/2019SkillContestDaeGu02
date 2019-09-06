#pragma once
#include "Scene.h"

class Stage1 :
	public Scene
{
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

