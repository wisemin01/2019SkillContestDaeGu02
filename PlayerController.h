#pragma once
#include "Component.h"

class Camera;
class Soldier;
class SelectRange;

template <typename T>
class FSM;

class PlayerController :
	public Component
{
	friend class PlayerControllerTutorial;
	friend class PlayerControllerStage1;
private:
	float m_fCameraMoveSpeed	= 3.2f;

	RECT	m_rcCameraRange		= { 0 };
	Camera* m_pCamera			= nullptr;
	SelectRange* m_pSelector	= nullptr;
	Timer*	m_pTimeAttackTimer	= nullptr;

	FSM<PlayerController>* m_pFSM = nullptr;

public:

	EventHandler<Vector3>		OnRightClick;
	EventHandler<RECT>			OnSelect;
	EventHandler<EmptyEventArg>	OnDeselect;
	EventHandler<EmptyEventArg>	OnStop;
	EventHandler<OutputString>	OnTalk;

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

	void Say(const OutputString& context);

private:
	inline static PlayerController* g_pMainPlayerController = nullptr;
	inline static bool g_bIsEndListenTutorial = true;
	inline static int g_iPlayerUnitCount = 0;

public:
	static PlayerController* GetMain() { return g_pMainPlayerController; }
	static int GetPlayerUnitCount() { return g_iPlayerUnitCount; }

	static void AddUnit() { g_iPlayerUnitCount++; }
	static void RemoveUnit() { g_iPlayerUnitCount--; }

	static bool IsClearTutorial() { return g_bIsEndListenTutorial; }
};