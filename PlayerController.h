#pragma once
#include "Component.h"

class Camera;
class Soldier;
class SelectRange;

class PlayerController :
	public Component
{
private:
	float m_fCameraMoveSpeed	= 3.2f;

	RECT	m_rcCameraRange		= { 0 };
	Camera* m_pCamera			= nullptr;
	SelectRange* m_pSelector	= nullptr;
public:

	EventHandler<Vector3>		OnRightClick;
	EventHandler<RECT>			OnSelect;
	EventHandler<EmptyEventArg>	OnDeselect;
	EventHandler<EmptyEventArg>	OnStop;

public:

	EventListener<RECT>	*		OnSelectListen;

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

	virtual void OnCollision(Collider* other) override;

	// PIVOT : LEFT TOP (0, 0)
	void SetCameraRange(float width, float height);

	// SoldierType:: 
	Soldier* SpawnSoldier(Vector3 position, int soldierType);

private:

	void CameraMoveInput();
	void CharacterMoveInput();
	void CameraPositionLimit();

	void OnSelectCommand(RECT rc);

public:

	inline static PlayerController* g_pMainPlayerController = nullptr;
};

#define MainPlayerController PlayerController::g_pMainPlayerController