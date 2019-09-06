#include "DXUT.h"
#include "Camera.h"

void Camera::Initialize()
{
	Set(Window::Width, Window::Height);

	// 메인 카메라가 아무것도 없다면 자동으로 메인 카메라가 된다.
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

	// 2d world 의 y축은 +/- 가 바뀌어있다.
	RENDER.SetTransformForDevice(D3DTS_PROJECTION, &Matrix::OrthoLH(width, -height, 0, 1));
}

void Camera::SetMain()
{
	g_pMainCamera = this;
}
