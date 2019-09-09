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

	m_pShakeTimer = Timer::Create(0);
}

void Camera::Update()
{
	if (m_listShakeInfos.empty() == false)
	{
		for (auto iter = m_listShakeInfos.begin(); iter != m_listShakeInfos.end();)
		{
			if (iter->timer->IsEnd == true)
			{
				Timer::Destroy(iter->timer);

				iter = m_listShakeInfos.erase(iter);
			}
			else
			{
				transform->Translate(
					Vector3(
						Random::Instance().Get(-iter->power, iter->power),
						Random::Instance().Get(-iter->power, iter->power), 0)
				);
				iter++;
			}
		}
	}


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

void Camera::Shake(float time, float power)
{
	m_listShakeInfos.push_back(ShakeInfo(Timer::Create(time), power));
}

void Camera::SetMain()
{
	g_pMainCamera = this;
}
