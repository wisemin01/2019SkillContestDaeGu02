#pragma once
/*
 * EventListener<T> :
 * �̺�Ʈ �����ʴ�
 * CreateListener(Type, Function) �� ���� ������ �� �̺�Ʈ �ڵ鷯�� ����Ͽ� ����մϴ�.
 * �̺�Ʈ�� �߻��� ������ ����� �Լ��� ����˴ϴ�.
 * T = �Լ� ���� Ÿ��.
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
 * �̺�Ʈ �ڵ鷯�� �̺�Ʈ �����ʵ��� �����ϴ� ��ü�Դϴ�.
 * �� �̺�Ʈ�� �߻����� �� �� �����ʿ��� ���ڸ� �����ϸ� ȣ���ų �� �ֽ��ϴ�.
 * T = �̺�Ʈ�� �߻����� �� ������ ���� Ÿ��.
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

	// ����� �ʿ����� ����
	void Detach(EventListener<T>* listener)
	{
		int key = (int)listener;

		auto find = m_mapListeners.find(key);

		if (find == m_mapListeners.end())
			return;

		m_mapListeners.erase(find);
	}

	// �ʿ��� ���� & �޸𸮱��� ����
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