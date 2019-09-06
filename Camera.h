#pragma once
#include "Component.h"

class Camera :
	public Component
{
private:

	Vector3 m_vLookAt = Vector3::Zero;

	int m_iWidth = 0;
	int m_iHeight = 0;

public:
	// ī�޶� ������Ʈ�� �������� ������ �⺻ Window::Width, Window::Height�� Projection�� �����ϴ�.
	Camera() {}
	~Camera() {}

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void Set(int width, int height);

	void SetMain();

	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }

	PropertyG(GetWidth) int Width;
	PropertyG(GetHeight) int Height;

public:

	inline static Camera* g_pMainCamera = nullptr;

	static Camera* MainCamera() { return g_pMainCamera; }
};