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

	// 새 엑터를 생성합니다.
	// DEFAULT_COMPONENT 메크로 옵션을 통해 기본으로 엑터에 내장할 컴포넌트를
	// 지정할 수 있습니다.
	Actor* Create(Tag tag = -1, bool isVisible = true, bool isActive = true);

	// 새 빈 엑터를 생성합니다.
	Actor* CreateEmpty(Tag tag = -1, bool isVisible = true, bool isActive = true);

	void Update();
	void Reset();
};

#define ACTOR ActorManager::GetInstance()