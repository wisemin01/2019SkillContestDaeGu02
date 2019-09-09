#include "DXUT.h"
#include "Rigidbody.h"

void Rigidbody::Initialize()
{
	Base->rigidbody = this;
}

void Rigidbody::Update()
{
	m_vVelocity += m_vForce;
	m_vForce = Vector3::Zero;

	transform->Position += m_vVelocity;

	m_vVelocity *= m_fFriction;
}

void Rigidbody::Release()
{
	if (Base->rigidbody == this)
		Base->rigidbody = nullptr;
}

void Rigidbody::OnCollision(Collider* other)
{
	if (other->IsTrigger == true)
		return;

	if (m_bIsPhysicalTreatment == false)
		return;

	Vector3 EndPosition = transform->Position;
	Vector3 TargetPosition = other->transform->Position;

	Vector3 Direction = EndPosition - TargetPosition;

	float Length = Direction.Length();

	Direction.Normalize();

	AddForce(Direction * Length * Time::Delta());
}

void Rigidbody::AddForce(const Vector3& force)
{
	m_vForce += force;
}

void Rigidbody::AddForce(const Vector2& force)
{
	m_vForce += Vector3(force.x, force.y, 0);
}

void Rigidbody::AddForce(float x, float y, float z)
{
	m_vForce += Vector3(x, y, z);
}

void Rigidbody::AddForce(float x, float y)
{
	m_vForce += Vector3(x, y, 0);
}

void Rigidbody::MovePosition(const Vector3& position)
{
	transform->Position = position;
}
