#include "DXUT.h"
#include "MainGame.h"

#include "Actor.h"
#include "Transform.h"

#include "IntroScene.h"
#include "Stage1.h"

void MainGame::Initialize()
{
	SCENE.Register<IntroScene>("INTRO");
	SCENE.Register<Stage1>("STAGE1");

	SCENE.Change("INTRO");
}

void MainGame::Update()
{
	Timer::UpdateTimers();
	InputManager::GetInstance().Update();

	SCENE.Update();
}

void MainGame::Render()
{
	SCENE.Render();
}

void MainGame::Release()
{
	ReleaseInstance(SceneManager);
	ReleaseInstance(ActorManager);
	ReleaseInstance(CollisionManager);
	ReleaseInstance(RenderManager);
	ReleaseInstance(ResourceManager);
	ReleaseInstance(InputManager);

	Timer::Clear();
}

void MainGame::LostDevice()
{
	RENDER.OnLostDevice();
}

void MainGame::ResetDevice()
{
	RENDER.OnResetDevice();
}
