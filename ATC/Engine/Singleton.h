#pragma once
NAMESPACE(Engine)
template <class T>
class Singleton
{
private:
	static T* instance;
protected:
public:
	static T* GetInstance(void)
	{
		if (instance == nullptr)
			instance = new T();
		return instance;
	}
};

template <class T> T* Singleton<T>::instance = nullptr;
END