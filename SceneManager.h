#pragma once
#include "Singleton.h"

class Scene;

class SceneManager :
	public Singleton<SceneManager>
{
	friend class MainGame;
private:
	std::map< std::string, Scene* > m_mapScenes;

	Scene* m_pNextScene = nullptr;
	Scene* m_pCurrentScene = nullptr;
public:
	SceneManager() {}
	~SceneManager() { Reset(); }

	template <typename T>
	void Register(const std::string& key)
	{
		if (auto find = m_mapScenes.find(key); find == m_mapScenes.end())
		{
			m_mapScenes.insert(std::make_pair(key, new T()));
		}
	}

	void Change(const std::string& targetSceneKey);

private:

	void Update();
	void Render();

	void Reset();
};

#define SCENE SceneManager::GetInstance()