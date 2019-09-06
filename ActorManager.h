#pragma once
#include "Singleton.h"

class Actor;

class ActorManager :
	public Singleton<ActorManager>
{
private:
	std::list< Actor* > m_listActors;

public:
	ActorManager() {}
	~ActorManager() { Reset(); }

	// �� ���͸� �����մϴ�.
	// DEFAULT_COMPONENT ��ũ�� �ɼ��� ���� �⺻���� ���Ϳ� ������ ������Ʈ��
	// ������ �� �ֽ��ϴ�.
	Actor* Create(Tag tag = -1, bool isVisible = true, bool isActive = true);

	// �� �� ���͸� �����մϴ�.
	Actor* CreateEmpty(Tag tag = -1, bool isVisible = true, bool isActive = true);

	void Update();
	void Reset();
};

#define ACTOR ActorManager::GetInstance()