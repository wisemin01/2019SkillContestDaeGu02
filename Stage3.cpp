#include "DXUT.h"
#include "Stage3.h"
#include "TextRenderer.h"

void Stage3::Initialize()
{
	Actor* pActor = ACTOR.CreateEmpty(TagType::None);
	pActor->AddComponent<Transform>();
	pActor->AddComponent<TextRenderer>()->Set("�����ý��丮 Bold", 50, L"Stage3 �� ���� �̱��� ���������Դϴ�.");
	pActor->transform->Position = Vector3(100, 100, 0);
}