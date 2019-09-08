#pragma once
#include "Component.h"

class StageSelectMap :
	public Component
{
private:

	Actor* m_pMapBase = nullptr;
	Actor* m_pButtonBase = nullptr;

	int m_iSelectMap = MapType::None;
	bool m_bIsEndSelect = false;
	bool m_bIsStart = false;

	Actor* m_pLevelPanel = nullptr;
	Actor* m_pBlackPanel = nullptr;

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

private:

	void OnSelectHaeundae(const EmptyEventArg& e);
	void OnSelectSeomyeon(const EmptyEventArg& e);
	void OnSelectBusanStation(const EmptyEventArg& e);
	void OnStartButtonClick(const EmptyEventArg& e);
	void OnShopButtonClick(const EmptyEventArg& e);
};

