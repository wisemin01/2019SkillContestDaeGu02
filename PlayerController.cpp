#include "DXUT.h"
#include "PlayerController.h"

#include "Camera.h"
#include "Soldier.h"
#include "SelectRange.h"
#include "FSM.h"
#include "HPModule.h"

#include "PlayerControllerTutorial.h"
#include "PlayerControllerStage1.h"

#include "BulletAttack.h"

void PlayerController::Initialize()
{
	SoundSource::Load("midnight-ride-01a", L"Sound/midnight-ride-01a.wav");
	SoundSource::Load("FTu1L", L"Sound/FTu1L.wav");

	AddComponent<Rigidbody>();
	m_pSelector = AddComponent<SelectRange>();
	m_pCamera	= AddComponent<Camera>();

	rigidbody->Friction = 0.9f;
	
	if (g_pMainPlayerController == nullptr)
		g_pMainPlayerController = this;

	OnSelectListen = CreateListener(RECT, OnSelectCommand);

	m_pSelector->OnSelect += OnSelectListen;

	m_pFSM = AddComponent<FSM<PlayerController>>();
	m_pFSM->SetOwner(this);
}

void PlayerController::Update()
{
#if DEBUG
	static bool bDebug6xSpeedMode = false;

	if (Input::GetKeyDown(KeyCode::P))
	{
		bDebug6xSpeedMode = !bDebug6xSpeedMode;

		Time::SetTimeScale(bDebug6xSpeedMode ? 4.0f : 1.0f);
	}
#endif

	if (Input::GetKeyPress(KeyCode::Space))
	{
		Actor* pFirstSoldier = ACTOR.FindActor(TagType::Player);

		if (pFirstSoldier)
			transform->Position = Vector3::Lerp(transform->Position, pFirstSoldier->transform->Position, 0.15f);
	}

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

void PlayerController::Say(const OutputString& context)
{
	OnTalk(context);
}
