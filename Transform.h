#pragma once
#include "Component.h"

class Transform :
	public Component
{
private:

	Vector3 m_vLocalPosition		= Vector3::Zero;
	Vector3 m_vLocalScale			= Vector3::One;
	float	m_fLocalRotation		= 0.0f;

	Transform* m_pParentTransform	= nullptr;

	bool m_bIsMatrixValueCaching	= false;

	Matrix m_mWorldMatrixCache		= Matrix::IdentityCoord;

private:

	void CalculateCacheData();

public:
	Transform();
	virtual ~Transform();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void Translate(const Vector3& v);
	void Scaling(float s);
	void Rotate(float value);
	
	Matrix GetWorldMatrix();

	void SetParent(Transform* parent);

public:

	Vector3 GetPosition();
	Vector3 GetScale();
	float GetRotation();

	Vector3 GetLocalPosition();
	Vector3 GetLocalScale();
	float GetLocalRotation();

	Transform* GetParent();

	void SetPosition(const Vector3& v);
	void SetScale(const Vector3& v);
	void SetRotation(float v);

public:

	PropertyGS(GetPosition, SetPosition) Vector3 Position;
	PropertyGS(GetScale, SetScale) Vector3 Scale;
	PropertyGS(GetRotation, SetRotation) float Rotation;

	PropertyG(GetLocalPosition) Vector3 LocalPosition;
	PropertyG(GetLocalScale) Vector3 LocalScale;
	PropertyG(GetLocalRotation) float LocalRotation;
};

