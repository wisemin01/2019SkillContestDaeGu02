#pragma once
/*
 * EventListener<T> :
 * 이벤트 리스너는
 * CreateListener(Type, Function) 을 통해 생성한 후 이벤트 핸들러에 등록하여 사용합니다.
 * 이벤트가 발생할 때마다 연결된 함수가 실행됩니다.
 * T = 함수 인자 타입.
*/
template <typename T>
class EventListener
{
	template <typename T>
	friend class EventHandler;
private:
	std::function< void(T) > m_Function;
public:
	EventListener(std::function<void(T)>&& func)
		: m_Function(func)
	{
		
	}
};

/*
 * EventHandler<T> :
 * 이벤트 핸들러는 이벤트 리스너들을 저장하는 객체입니다.
 * 새 이벤트가 발생했을 때 각 리스너에게 인자를 전달하며 호출시킬 수 있습니다.
 * T = 이벤트가 발생했을 때 전달할 인자 타입.
*/
template <typename T>
class EventHandler
{
private:

	std::map< int, EventListener<T>* > m_mapListeners;

public:
	~EventHandler()
	{
		for (auto iter : m_mapListeners)
		{
			SAFE_DELETE(iter.second);
		}

		m_mapListeners.clear();
	}

	inline void operator +=(EventListener<T>* listener)
	{
		AddListener(listener);
	}

	inline void operator -=(EventListener<T>* listener)
	{
		Detach(listener);
	}

	void AddListener(EventListener<T>* listener)
	{
		int key = (int)listener;

		if (auto find = m_mapListeners.find(key); find != m_mapListeners.end())
			return;

		m_mapListeners.insert(std::make_pair(key, listener));
	}

	// 저장된 맵에서만 삭제
	void Detach(EventListener<T>* listener)
	{
		int key = (int)listener;

		auto find = m_mapListeners.find(key);

		if (find == m_mapListeners.end())
			return;

		m_mapListeners.erase(find);
	}

	// 맵에서 삭제 & 메모리까지 해제
	void Remove(EventListener<T>* listener)
	{
		int key = (int)listener;

		auto find = m_mapListeners.find(key);

		if (find == m_mapListeners.end())
			return;

		m_mapListeners.erase(find);

		SAFE_DELETE(listener);
	}

	void operator()(const T& argument)
	{
		for (auto iter : m_mapListeners) {
			iter.second->m_Function(argument);
		}
	}
};

class EmptyEventArg {};

#define CreateListener(Type, Function) \
new EventListener<Type>([this](Type value){ Function(value); })