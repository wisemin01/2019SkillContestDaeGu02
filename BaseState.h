#pragma once

template <class T>
class BaseState abstract
{
	template <class T>
	friend class FSM;
protected:
	FSM<T>* m_pFSM = nullptr;
public:
	BaseState() {}
	virtual ~BaseState() {}

	virtual void Enter() = 0;
	virtual void Stay() = 0;
	virtual void Exit() = 0;

	void ChangeState(int type);

	void SetFSM(FSM<T>* fsm) { m_pFSM = fsm; }
};

template<class T>
inline void BaseState<T>::ChangeState(int type)
{
	m_pFSM->ChangeState(type);
}
