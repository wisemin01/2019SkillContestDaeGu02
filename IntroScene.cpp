#include "DXUT.h"
#include "IntroScene.h"
#include "Actor.h"
#include "PlayerController.h"
#include "Wobble.h"

void IntroScene::Initialize()
{
	// ================================================================
	// RESOURCE LOADING
	// ================================================================

	{
		Sprite::Load("Black", "UI/Black.png");
	}
}

void IntroScene::Update()
{
	ACTOR.Update();
	COLLISION.Update();

	SCENE.Change("STAGE1");
}

void IntroScene::Render()
{
	RENDER.Render();
}

void IntroScene::Release()
{
	ACTOR.Reset();
}
