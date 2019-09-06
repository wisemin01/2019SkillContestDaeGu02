#pragma once
#include "Singleton.h"

#include "KeyCode.hpp"

class InputManager :
	public Singleton<InputManager>
{
private:
	bool m_bCurrentKey[256] = { false };
	bool m_bPrevKey[256] = { false };

public:

	void Update();

	bool GetKeyDown(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKeyPress(KeyCode key);

	Vector3 GetMousePosition();
};

Vector3 ScreenToWorld(const Vector3& screen);
Vector3 WorldToScreen(const Vector3& world);
Vector2 ScreenToWorld(const Vector2& screen);
Vector2 WorldToScreen(const Vector2& world);

// INPUT CLASS : to make access easier
static class Input
{
public:
	static inline bool GetKeyDown(KeyCode key)
	{
		return InputManager::GetInstance().GetKeyDown(key);
	}
	static inline bool GetKeyUp(KeyCode key)
	{
		return InputManager::GetInstance().GetKeyUp(key);
	}
	static inline bool GetKeyPress(KeyCode key)
	{
		return InputManager::GetInstance().GetKeyPress(key);
	}

	static inline Vector3 GetMousePosition()
	{
		return InputManager::GetInstance().GetMousePosition();
	}
};