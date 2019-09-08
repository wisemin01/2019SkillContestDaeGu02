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
	Actor* Create(Tag tag = -1, bool isVisible = true, bool isActive = true, int layer = 0);
	Actor* Create(Tag tag, int layer);

	// 새 빈 엑터를 생성합니다.
	Actor* CreateEmpty(Tag tag = -1, bool isVisible = true, bool isActive = true);

	// 태그에 맞는 엑터를 가져옵니다.
	// 가장 첫번째로 존재하는 객체를 가져옵니다.
	Actor* FindActor(Tag tag);

	void Update();
	void Reset();
};

#define ACTOR ActorManager::GetInstance()