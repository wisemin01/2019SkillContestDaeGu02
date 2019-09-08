#include "DXUT.h"
#include "Scene.h"

void Scene::UpdateBase()
{
	if (m_SceneProperty.AutoUpdate)
		ACTOR.Update();

	if (m_SceneProperty.AutoCollisionCheck)
		COLLISION.Update();

	if (m_SceneProperty.AutoSort)
		RENDER.Sort();
}

void Scene::RenderBase()
{
	if (m_SceneProperty.AutoRender)
		RENDER.Render();
}

void Scene::ReleaseBase()
{
	if (m_SceneProperty.AutoClearOnReleaseScene)
		ACTOR.Reset();
}
