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
	Actor* Create(Tag tag = -1, bool isVisible = true, bool isActive = true, int layer = 0);
	Actor* Create(Tag tag, int layer);

	// �� �� ���͸� �����մϴ�.
	Actor* CreateEmpty(Tag tag = -1, bool isVisible = true, bool isActive = true);

	// �±׿� �´� ���͸� �����ɴϴ�.
	// ���� ù��°�� �����ϴ� ��ü�� �����ɴϴ�.
	Actor* FindActor(Tag tag);

	void Update();
	void Reset();
};

#define ACTOR ActorManager::GetInstance()