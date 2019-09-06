#include "DXUT.h"
#include "InputManager.h"

#include "Camera.h"

void InputManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		m_bPrevKey[i] = m_bCurrentKey[i];
		m_bCurrentKey[i] = (bool)GetAsyncKeyState(i);
	}
}

bool InputManager::GetKeyDown(KeyCode key)
{
	return !m_bPrevKey[(int)key] && m_bCurrentKey[(int)key];
}

bool InputManager::GetKeyUp(KeyCode key)
{
	return m_bPrevKey[(int)key] && !m_bCurrentKey[(int)key];
}

bool InputManager::GetKeyPress(KeyCode key)
{
	return m_bPrevKey[(int)key] && m_bCurrentKey[(int)key];
}

Vector3 InputManager::GetMousePosition()
{
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	return Vector3((float)pt.x, (float)pt.y, 0);
}

Vector3 ScreenToWorld(const Vector3& screen)
{
	return screen + (Camera::MainCamera()->transform->Position - Window::Center);
}

Vector3 WorldToScreen(const Vector3& world)
{
	return world - (Camera::MainCamera()->transform->Position - Window::Center);
}

Vector2 ScreenToWorld(const Vector2& screen)
{
	return screen + Vector2(Camera::MainCamera()->transform->Position - Window::Center);
}

Vector2 WorldToScreen(const Vector2& world)
{
	return world - Vector2(Camera::MainCamera()->transform->Position - Window::Center);
}
