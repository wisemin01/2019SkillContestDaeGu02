#include "DXUT.h"
#include "Stage2.h"
#include "TextRenderer.h"

void Stage2::Initialize()
{
	Actor* pActor = ACTOR.CreateEmpty(TagType::None);
	pActor->AddComponent<Transform>();
	pActor->AddComponent<TextRenderer>()->Set("메이플스토리 Bold", 50, L"Stage2 는 아직 미구현 스테이지입니다.");
	pActor->transform->Position = Vector3(100, 100, 0);
}

