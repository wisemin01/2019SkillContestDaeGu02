#include "DXUT.h"
#include "IntroScene.h"
#include "Actor.h"
#include "Button.h"
#include "Fade.h"
#include "Camera.h"
#include "StageSelectMap.h"
#include "TextRenderer.h"

void IntroScene::Initialize()
{
	// ================================================================
	// RESOURCE LOADING
	// ================================================================

	{
		Sprite::Load("menu-background", "Mainmenu/background.png");
		Sprite::Load("busan-station", "Mainmenu/busan-station.png");
		Sprite::Load("coin-background", "Mainmenu/coin-background.png");
		Sprite::Load("haeundae", "Mainmenu/haeundae.png");
		Sprite::Load("level-button", "Mainmenu/level-%d.png", 3);
		Sprite::Load("seo-myeon", "Mainmenu/seo-myeon.png");
		Sprite::Load("shop-background", "Mainmenu/shop-background.png");
		Sprite::Load("shop-button", "Mainmenu/shop-button.png");
		Sprite::Load("stage-map", "Mainmenu/stage-map.png");
		Sprite::Load("start-button", "Mainmenu/start-button.png");
		Sprite::Load("time-panel", "Mainmenu/time-panel.png");

		Sprite::Load("Black", "UI/Black.png");
	}

	// ================================================================
	// BACKGROUND OBJECTS
	// ================================================================

	{
		Actor* pBackground = ACTOR.Create(TagType::Background, true, true, 0);
		pBackground->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("menu-background")));
		pBackground->renderer->Change(UnitStateType::Idle);
		pBackground->transform->Position = Window::Center;

		Actor* pStageMap = ACTOR.Create(TagType::Background);
		pStageMap->AddComponent<StageSelectMap>();
	}

	{
		Actor* pCamera = ACTOR.Create(TagType::Camera);
		pCamera->AddComponent<Camera>();
		pCamera->transform->Position = Window::Center;
	}
}

void IntroScene::Update()
{
	ACTOR.Update();
	COLLISION.Update();
}

void IntroScene::Render()
{
	RENDER.Render();
}

void IntroScene::Release()
{
	ACTOR.Reset();
}
