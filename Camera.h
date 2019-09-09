#pragma once
#include "Component.h"

class Camera :
	public Component
{
	struct ShakeInfo
	{
		Timer* timer = nullptr;
		float power = 0.0f;

		ShakeInfo(Timer* timer, float power)
			: timer(timer), power(power) {}
	};
private:

	Vector3 m_vLookAt = Vector3::Zero;

	int m_iWidth = 0;
	int m_iHeight = 0;

	Timer* m_pShakeTimer = nullptr;
	bool m_bShakeOn = false;
	float m_fShakePower = 10.0f;

	std::list<ShakeInfo> m_listShakeInfos;

public:
	// 카메라 컴포넌트는 설정하지 않으면 기본 Window::Width, Window::Height의 Projection을 가집니다.
	Camera() {}
	~Camera() {}

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void Set(int width, int height);

	void Shake(float time, float power);
	void SetMain();

	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }

	PropertyG(GetWidth) int Width;
	PropertyG(GetHeight) int Height;

private:
	inline static Camera* g_pMainCamera = nullptr;

public:
	static Camera* MainCamera() { return g_pMainCamera; }
};