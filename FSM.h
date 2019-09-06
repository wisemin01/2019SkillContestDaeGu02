#pragma once
#include "Component.h"

template <class OWNER>
class BaseState;

template <class OWNER>
class FSM :
	public Component
{
private:
	std::map< int, BaseState<OWNER>* > m_mapStates;

	BaseState<OWNER>* m_pCurrentState	= nullptr;
	BaseState<OWNER>* m_pNextState		= nullptr;

	OWNER* m_pOwner = nullptr;

	int m_iCurrentStateIndex = -1;

public:
	FSM() {}
	~FSM() {}

	void AddState(int key, BaseState<OWNER>* state);
	void ChangeState(int key);

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void DebugView();

	int GetCurrentStatekey();

public:

	void SetOwner(OWNER* owner) { m_pOwner = owner; }
	OWNER* GetOwner() {

		if (m_pOwner == nullptr)
		{
			throw exception("FSM<OWNER>::GetOwner() - 'm_pOwner' menber variable was not initialized.\n\
				First call the FSM<OWNER>::SetOwner() function on the owner object.");
		}

		return m_pOwner; 
	}

	PropertyGS(GetOwner, SetOwner) OWNER* Owner;
};

#include "FSM.hpp"