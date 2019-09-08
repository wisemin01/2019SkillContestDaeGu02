#include "DXUT.h"
#include "Transform.h"

#include "Actor.h"


Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Initialize()
{
	Base->transform = this;
}

void Transform::Update()
{
}

void Transform::Release()
{
	if (Base->transform == this)
		Base->transform = nullptr;
}

void Transform::Translate(const Vector3& v)
{
	m_vLocalPosition += v;
}

void Transform::Scaling(float s)
{
	m_vLocalScale *= s;
}

Matrix Transform::GetWorldMatrix()
{
	Matrix world = Matrix::Scaling(m_vLocalScale)
		* Matrix::RotationZ(m_fLocalRotation)
		* Matrix::Translation(m_vLocalPosition);

	if (m_pParentTransform != nullptr)
		world *= m_pParentTransform->GetWorldMatrix();

	return world;
}

void Transform::SetParent(Transform* parent)
{
	m_pParentTransform = parent;
}

void Transform::AddChlid(Transform* chlid)
{
	chlid->SetParent(this);
}

Vector3 Transform::GetPosition() const
{
	if (m_pParentTransform)
	{
		return m_vLocalPosition + m_pParentTransform->GetPosition();
	}

	return m_vLocalPosition;
}

Vector3 Transform::GetScale() const
{
	if (m_pParentTransform)
	{
		return m_vLocalScale * m_pParentTransform->GetScale();
	}

	return m_vLocalScale;
}

float Transform::GetRotation() const
{
	if (m_pParentTransform)
	{
		return m_fLocalRotation + m_pParentTransform->GetRotation();
	}

	return m_fLocalRotation;
}

Vector3 Transform::GetLocalPosition()
{
	return m_vLocalPosition;
}

Vector3 Transform::GetLocalScale()
{
	return m_vLocalScale;
}

float Transform::GetLocalRotation()
{
	return m_fLocalRotation;
}

Transform* Transform::GetParent()
{
	return m_pParentTransform;
}

void Transform::SetPosition(const Vector3& v)
{
	m_vLocalPosition = v;
}

void Transform::SetScale(const Vector3& v)
{
	m_vLocalScale = v;
}

void Transform::SetRotation(float v)
{
	m_fLocalRotation = v;
}

void Transform::Rotate(float value)
{
	m_fLocalRotation = value;
}
