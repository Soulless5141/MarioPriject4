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
/// �C���X�^���X�폜����
/// </summary>
	static T* DeleteInstance(T* instance)
	{
		// �C���X�^���X�����݂��Ă���ꍇ�A�폜����
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
		return instance;
	}
};



