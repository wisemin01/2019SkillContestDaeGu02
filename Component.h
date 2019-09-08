#pragma once

class Actor;

class Transform;
class Renderer;
class Collider;
class Rigidbody;

/*
 *	컴포넌트는 Actor 객체의 컨테이너에 담겨 동작하며
 *  새로 재정의하여 사용자 정의 컴포넌트를 생성할 수 있습니다.
*/
class Component
{
	friend class Actor;
private:

	Actor* m_pBaseActor = nullptr;

public:
	Component() {}
	virtual ~Component() {}

	// 처음 컴포넌트가 초기화 될 때 호출됩니다.
	virtual void Initialize() = 0;
	// 매 프레임 호출되는 함수입니다.
	virtual void Update() = 0;
	// 매 프레임 호출되는 함수입니다. Update() 프레임이 모두 실행된 뒤 호출됩니다.
	virtual void LateUpdate() {}
	// 컴포넌트가 파괴될 때 호출됩니다.
	virtual void Release() = 0;

protected:

	// 객체가 보이게 되었을 때 호출됩니다.
	virtual void OnVisible() {}
	// 객체가 보이지 않게 되었을 때 호출됩니다.
	virtual void OnUnvisible() {}
	// 객체가 활성화 되었을 때 호출됩니다.
	virtual void OnEnable() {}
	// 객체가 비활성화 되었을 때 호출됩니다.
	virtual void OnDisable() {}
	// 객체가 파괴될 때 호출됩니다. < Destroy( Actor* ) 함수로 인해 호출됩니다. >
	virtual void OnDestroy() {}
	// 객체가 충돌될 때 호출됩니다. Collider* 컴포넌트가 추가되어 있는 상태에서만 호출됩니다.
	virtual void OnCollision(Collider* other) {}

	// 해당 target 객체를 파괴합니다.
	void Destroy(Actor* target);

public:

	// 새 컴포넌트를 추가합니다.
	// 같은 타입의 컴포넌트는 중복되어 추가되지 않습니다.
	// 반환 : 중복시 기존 컴포넌트
	template <class COM>
	COM* AddComponent();

	// 해당 타입의 컴포넌트를 가져옵니다.
	// 호출 비용 : std::map<>::find() , static_cast<>
	template <class COM>
	COM* GetComponent();

	// 이 컴포넌트를 소지한 Actor 객체를 가져옵니다.
	PropertyG(GetActor) Actor* Base;

	// Transform 객체를 가져옵니다. 없는 경우 nullptr 를 반환합니다.
	PropertyG(GetTransform) Transform* transform;
	// Renderer 객체를 가져옵니다. 없는 경우 nullptr 를 반환합니다.
	PropertyG(GetRenderer) Renderer* renderer;
	// Collider 객체를 가져옵니다. 없는 경우 nullptr 를 반환합니다.
	PropertyG(GetCollider) Collider* collider;
	// Rigidbody 객체를 가져옵니다. 없는 경우 nullptr 를 반환합니다.
	PropertyG(GetRigidbody) Rigidbody* rigidbody;

private:

	// Actor 객체를 설정합니다.
	inline void SetActor(Actor* actor) { m_pBaseActor = actor; }

public:

	inline Actor* GetActor() const { return m_pBaseActor; }

	Transform* GetTransform() const;
	Renderer* GetRenderer() const;
	Collider* GetCollider() const;
	Rigidbody* GetRigidbody() const;
};

#include "Component.hpp"