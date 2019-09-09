#include "FSM.h"
#pragma once

template<class OWNER>
inline void FSM<OWNER>::AddState(int key, BaseState<OWNER>* state)
{
	if (auto find = m_mapStates.find(key); find == m_mapStates.end())
	{
		state->m_pFSM = this;

		m_mapStates.insert(std::make_pair(key, state));
	}
}

template<class OWNER>
inline void FSM<OWNER>::ChangeState(int key)
{
	if (auto find = m_mapStates.find(key); find != m_mapStates.end())
	{
		m_pNextState = find->second;
		m_iCurrentStateIndex = key;
		return;
	}

	throw exception("FSM<OWNER>::ChangeState(int key) - Invalid key value.");
}

template<class OWNER>
inline void FSM<OWNER>::Initialize()
{
}

template<class OWNER>
inline void FSM<OWNER>::Update()
{
	if (m_pNextState)
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->Exit();
		}

		m_pNextState->Enter();

		{
			m_pCurrentState = nullptr;

			m_pCurrentState = m_pNextState;

			m_pNextState = nullptr;
		}
	}

	if (m_pCurrentState)
	{
		m_pCurrentState->Stay();
	}
}

template<class OWNER>
inline void FSM<OWNER>::LateUpdate()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->LateStay();
	}
}

template<class OWNER>
inline void FSM<OWNER>::Release()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->Exit();
	}

	for (auto iter : m_mapStates)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapStates.clear();
}

template<class OWNER>
inline void FSM<OWNER>::DebugView()
{
	Log(" [FSM::DebugView] Owner Class :: " << typeid(OWNER).name());
	Log(" ======= State Classes =======");

	for (auto iter : m_mapStates)
	{
		Log(typeid(*iter.second).name());
	}
}

template<class OWNER>
inline int FSM<OWNER>::GetCurrentStatekey()
{
	return m_iCurrentStateIndex;
}
