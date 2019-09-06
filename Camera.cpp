#include "DXUT.h"
#include "Camera.h"

void Camera::Initialize()
{
	Set(Window::Width, Window::Height);

	// ���� ī�޶� �ƹ��͵� ���ٸ� �ڵ����� ���� ī�޶� �ȴ�.
	if (MainCamera() == nullptr)
	{
		SetMain();
	}
}

void Camera::Update()
{
	RENDER.SetTransformForDevice(D3DTS_VIEW, &Matrix::View2D(transform->Position, transform->Scale, 0));
}

void Camera::Release()
{
	if (g_pMainCamera == this)
		g_pMainCamera = nullptr;
}

void Camera::Set(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;

	// 2d world �� y���� +/- �� �ٲ���ִ�.
	RENDER.SetTransformForDevice(D3DTS_PROJECTION, &Matrix::OrthoLH(width, -height, 0, 1));
}

void Camera::SetMain()
{
	g_pMainCamera = this;
}
