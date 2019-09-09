#include "DXUT.h"
#include "PlayerControllerTutorial.h"

#include "FSM.h"
#include "PlayerController.h"
#include "TextBox.h"
#include "OperatorUnit.h"
#include "TextRenderer.h"
#include "Fade.h"
#include "Camera.h"
#include "Wobble.h"
#include "EnemyController.h"
#include "Trigger.h"

void PlayerControllerTutorial::Say_Tutorial_Text01()
{
	m_pMissionPanelText->SetContext(L"현재 미션이 없습니다.");

	SoundSource::Load("mission-success", L"Sound/mission-success.wav")->Play();

	Base->Say(L"잘 하셨어요!");
	Base->Say(L"선택된 함선들은\n마우스 우클릭으로 이동시킬 수 있어요.");
	Base->Say(L"마우스 우클릭으로\n함선들을 이동시켜보세요.");

	m_bIsDisplayQuest[1] = true;
}

void PlayerControllerTutorial::Say_Tutorial_Text02()
{
	m_pMissionPanelText->SetContext(L"현재 미션이 없습니다.");

	SoundSource::Load("mission-success", L"Sound/mission-success.wav")->Play();

	Base->Say(L"잘 하셨어요!");
	Base->Say(L"이제 함선들을 이동시켜\n적 함선들을 찾아\n모두 파괴해주세요.");
	Base->Say(L"적 함선들을 모두 처치해야\n해운대에 함선들을\n정박시킬 수 있어요.");
	
	m_bIsDisplayQuest[2] = true;
}

void PlayerControllerTutorial::Say_Tutorial_Text03(bool flag)
{
	m_pMissionPanelText->SetContext(L"현재 미션이 없습니다.");

	if (flag == true) 
	{
		Base->Say(L"잘 하셨어요!");
		Base->Say(L"제가 알려드리는 건 여기까지에요.\n수고하셨습니다.");
		Base->Say(L"이제 오른쪽으로 함선들을\n이동시켜서 배를 정박시켜 주세요.");

		m_pStageEndTrigger = ACTOR.Create(TagType::None);

		auto trigger = m_pStageEndTrigger->AddComponent<Trigger>();
		trigger->collider->SetRange(300, 1125);
		trigger->OnTriggerStay += CreateListener(Collider*, OnAnchorCommand);

		m_pStageEndTrigger->transform->Position = Vector3(1900, 562.5, 0);

		m_bIsDisplayQuest[3] = true;
	}
	else
	{
		Base->Say(L"아군의 함선이 모두 파괴되었어요...");
		Base->Say(L"잠시 뒤 다시 작전이 시작될테니\n조금만 더 열심히 해주세요.");

		m_bIsTutorialFailed = true;
	}
}
