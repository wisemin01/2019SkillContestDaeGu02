#pragma once

class Scene abstract
{
	friend class SceneManager;
protected:
	Scene() {}
	virtual ~Scene() {}

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

