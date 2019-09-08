#include "DXUT.h"
#include "SceneManager.h"

#include "Scene.h"

void SceneManager::Change(const std::string& targetSceneKey)
{
	if (auto find = m_mapScenes.find(targetSceneKey); find != m_mapScenes.end())
	{
		m_pNextScene = find->second;
	}
}

void SceneManager::Update()
{
	if (m_pNextScene)
	{
		if (m_pCurrentScene)
		{
			m_pCurrentScene->Release();
			m_pCurrentScene->ReleaseBase();
		}

		m_pNextScene->Initialize();

		{
			m_pCurrentScene = nullptr;

			m_pCurrentScene = m_pNextScene;

			m_pNextScene = nullptr;
		}
	}

	if (m_pCurrentScene)
	{
		m_pCurrentScene->Update();
		m_pCurrentScene->UpdateBase();
	}
}

void SceneManager::Render()
{
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Render();
		m_pCurrentScene->RenderBase();
	}
}

void SceneManager::Reset()
{
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Release();
		m_pCurrentScene->ReleaseBase();
	}

	for (auto iter : m_mapScenes)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapScenes.clear();
}
