#pragma once

template <class T>
class Singleton {
protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	Singleton(const Singleton&) = default;
	Singleton& operator = (const Singleton&) = default;

public:

	static T* Get()
	{
		static T* instance;
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}

	/// <summary>
/// インスタンス削除処理
/// </summary>
	static T* DeleteInstance(T* instance)
	{
		// インスタンスが存在している場合、削除する
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
		return instance;
	}
};



