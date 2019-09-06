#include "DXUT.h"
#include "PlayerController.h"

#include "Camera.h"
#include "Soldier.h"
#include "SelectRange.h"

void PlayerController::Initialize()
{
	AddComponent<Rigidbody>();
	m_pSelector = AddComponent<SelectRange>();
	m_pCamera	= AddComponent<Camera>();

	rigidbody->Friction = 0.9f;
	
	SetCameraRange(2000, 1125);

	if (g_pMainPlayerController == nullptr)
		g_pMainPlayerController = this;

	OnSelectListen = CreateListener(RECT, OnSelectCommand);

	m_pSelector->OnSelect += OnSelectListen;
}

void PlayerController::Update()
{
	CameraMoveInput();
	CharacterMoveInput();
}

void PlayerController::LateUpdate()
{
	CameraPositionLimit();
}

void PlayerController::Release()
{
	if (g_pMainPlayerController == this)
		g_pMainPlayerController = nullptr;
}

void PlayerController::OnCollision(Collider* other)
{

}

void PlayerController::SetCameraRange(float width, float height)
{
	SetRect(&m_rcCameraRange, 0, 0, width, height);
}

Soldier* PlayerController::SpawnSoldier(Vector3 position, int soldierType)
{
	if (soldierType == SoldierType::Ship)
	{
		Actor* pShip = ACTOR.Create(TagType::Player);

		Soldier* pSoldier = pShip->AddComponent<Soldier>();

		pSoldier->transform->Position = position;

		return pSoldier;
	}
}

void PlayerController::CameraMoveInput()
{
	Vector3 Mouse = Input::GetMousePosition();
	constexpr float Gap = 30.0f;

	if (Mouse.x >= (Window::Width - Gap))
	{
		// CAMERA MOVE : GO TO RIGHT DIRECTION
		rigidbody->AddForce(m_fCameraMoveSpeed, 0);
	}
	if (Mouse.x <= (Gap))
	{
		// CAMERA MOVE : GO TO LEFT DIRECTION
		rigidbody->AddForce(-m_fCameraMoveSpeed, 0);
	}
	if (Mouse.y >= (Window::Height - Gap))
	{
		// CAMERA MOVE : GO TO DOWN DIRECTION
		rigidbody->AddForce(0, m_fCameraMoveSpeed);
	}
	if (Mouse.y <= (Gap))
	{
		// CAMERA MOVE : GO TO UP DIRECTION
		rigidbody->AddForce(0, -m_fCameraMoveSpeed);
	}
}

void PlayerController::CharacterMoveInput()
{
	if (Input::GetKeyDown(KeyCode::RightMouse))
	{
		OnRightClick(ScreenToWorld(Input::GetMousePosition()));
	}

	if (Input::GetKeyDown(KeyCode::A))
	{
		OnSelect(m_rcCameraRange);
	}

	if (Input::GetKeyDown(KeyCode::S))
	{
		OnStop(EmptyEventArg());
	}
}

void PlayerController::CameraPositionLimit()
{
	Vector3 camPos = m_pCamera->transform->Position;

	Vector2 camSize;
	camSize.x = (float)m_pCamera->Width;
	camSize.y = (float)m_pCamera->Height;

	if (camPos.x - Half(camSize.x) <= m_rcCameraRange.left)
		camPos.x = Half(camSize.x) + m_rcCameraRange.left;

	if (camPos.x + Half(camSize.x) >= m_rcCameraRange.right)
		camPos.x = -Half(camSize.x) + m_rcCameraRange.right;

	if (camPos.y - Half(camSize.y) <= m_rcCameraRange.top)
		camPos.y = Half(camSize.y) + m_rcCameraRange.top;
	
	if (camPos.y + Half(camSize.y) >= m_rcCameraRange.bottom)
		camPos.y = -Half(camSize.y) + m_rcCameraRange.bottom;

	m_pCamera->transform->Position = camPos;
}

void PlayerController::OnSelectCommand(RECT rc)
{
	OnSelect(rc);
}
