#include "DXUT.h"
#include "StageSelectMap.h"
#include "Fade.h"
#include "Button.h"
#include "Camera.h"

void StageSelectMap::Initialize()
{
	m_iSelectMap = MapType::Haeundae;

	// ================================================================
	// MAP OBJECTS
	// ================================================================

	{
		Actor* pMapBackground = ACTOR.Create(TagType::Background, true, true, 1);
		pMapBackground->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("stage-map")));
		pMapBackground->renderer->Change(UnitStateType::Idle);
		pMapBackground->transform->Position = Vector3(470, 360, 0);

		Actor* pHaeundae = ACTOR.Create(TagType::Button, true, true, 2);
		pHaeundae->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("haeundae")));
		pHaeundae->renderer->Change(UnitStateType::Idle);
		pHaeundae->transform->Position = Vector3(377, 523, 0);
		pHaeundae->AddComponent<Button>()->OnButtonClick += CreateListener(EmptyEventArg, OnSelectHaeundae);

		Actor* pSeomyeon = ACTOR.Create(TagType::Button, true, true, 2);
		pSeomyeon->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("seo-myeon")));
		pSeomyeon->renderer->Change(UnitStateType::Idle);
		pSeomyeon->transform->Position = Vector3(406, 288, 0);
		pSeomyeon->AddComponent<Button>()->OnButtonClick += CreateListener(EmptyEventArg, OnSelectSeomyeon);

		Actor* pBusanStation = ACTOR.Create(TagType::Button, true, true, 2);
		pBusanStation->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("busan-station")));
		pBusanStation->renderer->Change(UnitStateType::Idle);
		pBusanStation->transform->Position = Vector3(683, 353, 0);
		pBusanStation->AddComponent<Button>()->OnButtonClick += CreateListener(EmptyEventArg, OnSelectBusanStation);

		m_pMapBase = ACTOR.Create(TagType::Background);

		m_pMapBase->AddChlid(pMapBackground);
		m_pMapBase->AddChlid(pHaeundae);
		m_pMapBase->AddChlid(pSeomyeon);
		m_pMapBase->AddChlid(pBusanStation);
	}
	
	// ================================================================
	// BUTTON OBJECTS
	// ================================================================

	{
		Actor* pGameStart = ACTOR.Create(TagType::Button, true, true, 1);
		pGameStart->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("start-button")));
		pGameStart->renderer->Change(UnitStateType::Idle);
		pGameStart->transform->Position = Vector3(1068, 582, 0);
		pGameStart->AddComponent<Button>()->OnButtonClick += CreateListener(EmptyEventArg, OnStartButtonClick);

		Actor* pShop = ACTOR.Create(TagType::Button, true, true, 1);
		pShop->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("shop-button")));
		pShop->renderer->Change(UnitStateType::Idle);
		pShop->transform->Position = Vector3(1115, 270, 0);
		pShop->AddComponent<Button>()->OnButtonClick += CreateListener(EmptyEventArg, OnShopButtonClick);

		Actor* pGoldView = ACTOR.Create(TagType::Button, true, true, 1);
		pGoldView->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("coin-background")));
		pGoldView->renderer->Change(UnitStateType::Idle);
		pGoldView->transform->Position = Vector3(1115, 160, 0);
		
		Actor* pLevelView = ACTOR.Create(TagType::Button, true, true, 1);
		pLevelView->renderer->AddAnimation(1, new Animation(Sprite::Find("level-button")->Get(0)));
		pLevelView->renderer->AddAnimation(2, new Animation(Sprite::Find("level-button")->Get(1)));
		pLevelView->renderer->AddAnimation(3, new Animation(Sprite::Find("level-button")->Get(2)));
		pLevelView->renderer->Change(1);
		pLevelView->transform->Position = Vector3(984, 445, 0);

		Actor* pTimeView = ACTOR.Create(TagType::Button, true, true, 1);
		pTimeView->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("time-panel")));
		pTimeView->renderer->Change(UnitStateType::Idle);
		pTimeView->transform->Position = Vector3(1148, 445, 0);

		m_pLevelPanel = pLevelView;

		m_pButtonBase = ACTOR.Create(TagType::Background);

		m_pButtonBase->AddChlid(pGameStart);
		m_pButtonBase->AddChlid(pShop);
		m_pButtonBase->AddChlid(pGoldView);
		m_pButtonBase->AddChlid(pLevelView);
		m_pButtonBase->AddChlid(pTimeView);
	}

	// ================================================================
	// FADE
	// ================================================================

	{
		Actor* pBlackFadePanel = ACTOR.Create(TagType::UI, true, true, 10);

		pBlackFadePanel->renderer->RenderType = RenderType::UI;
		pBlackFadePanel->renderer->AddAnimation(UnitStateType::Idle, new Animation(Sprite::Find("Black")));
		pBlackFadePanel->renderer->Change(UnitStateType::Idle);

		pBlackFadePanel->transform->Position = Window::Center;

		pBlackFadePanel->renderer->CurrentAnime->AnimeColor = Color::White;
		pBlackFadePanel->AddComponent<Fade<Color>>()->Set(Color(1, 1, 1, 0), FadeTarget::Renderer_Alpha, -0.35f);

		m_pBlackPanel = pBlackFadePanel;
	}

	m_pMapBase->transform->Position = Vector3(0, 200, 0);
	m_pMapBase->transform->Rotation = D3DXToRadian(-90);
	m_pButtonBase->transform->Position = Vector3(1000, 0, 0);
}

void StageSelectMap::Update()
{
	constexpr float lerp_speed = 2.5;

	Camera::MainCamera()->transform->Scale =
		Lerp(Camera::MainCamera()->transform->Scale, Vector3::One, 0.1f);

	if (m_bIsStart == false)
	{
		if (Input::GetKeyDown(KeyCode::LeftMouse))
		{
			m_bIsStart = false;
		}

		return;
	}

	if (m_bIsEndSelect == true)
	{
		m_pMapBase->transform->Position = Vector3::Lerp(m_pMapBase->transform->Position, Vector3(0, 200, 0), Time::Delta() * lerp_speed);
		m_pMapBase->transform->Rotation = Lerp(m_pMapBase->transform->Rotation, D3DXToRadian(-90), Time::Delta() * lerp_speed);
		m_pButtonBase->transform->Position = Vector3::Lerp(m_pButtonBase->transform->Position, Vector3(1000, 0, 0), Time::Delta() * lerp_speed);

		if (m_pBlackPanel->renderer->CurrentAnime->GetAlpha() >= 1.0f)
		{
			switch (m_iSelectMap)
			{
			case MapType::Haeundae:
				SCENE.Change("STAGE1");
				break;

			case MapType::Seomyeon:
				SCENE.Change("STAGE2");
				break;

			case MapType::Busan_station:
				SCENE.Change("STAGE3");
				break;
			}
		}
	}
	else
	{
		m_pMapBase->transform->Position = Vector3::Lerp(m_pMapBase->transform->Position, Vector3::Zero, Time::Delta() * lerp_speed);
		m_pMapBase->transform->Rotation = Lerp(m_pMapBase->transform->Rotation, 0.0f, Time::Delta() * lerp_speed);
		m_pButtonBase->transform->Position = Vector3::Lerp(m_pButtonBase->transform->Position, Vector3::Zero, Time::Delta() * lerp_speed);
	}
}

void StageSelectMap::Release()
{
}

void StageSelectMap::OnSelectHaeundae(const EmptyEventArg& e)
{
	m_iSelectMap = MapType::Haeundae;
	m_pLevelPanel->renderer->Change(1);
	Camera::MainCamera()->transform->Scale = Vector3(1.05, 1.05, 1.05);
}

void StageSelectMap::OnSelectSeomyeon(const EmptyEventArg& e)
{
	m_iSelectMap = MapType::Seomyeon;
	m_pLevelPanel->renderer->Change(2);
	Camera::MainCamera()->transform->Scale = Vector3(1.05, 1.05, 1.05);
}

void StageSelectMap::OnSelectBusanStation(const EmptyEventArg& e)
{
	m_iSelectMap = MapType::Busan_station;
	m_pLevelPanel->renderer->Change(3);
	Camera::MainCamera()->transform->Scale = Vector3(1.05, 1.05, 1.05);
}

void StageSelectMap::OnStartButtonClick(const EmptyEventArg& e)
{
	m_bIsEndSelect = true;
	m_pBlackPanel->GetComponent<Fade<Color>>()->Set(Color(1, 1, 1, 1), FadeTarget::Renderer_Alpha, 0.45f);
}

void StageSelectMap::OnShopButtonClick(const EmptyEventArg& e)
{

}
