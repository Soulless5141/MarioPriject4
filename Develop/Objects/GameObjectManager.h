#pragma once


#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"
#include "../Utility/ResourceManager.h"
#include "GameObject.h"

#include <string>


#define D_OBJECT_SIZE	(32.0f)			// �ǂ̃T�C�Y

// �Q�[���I�u�W�F�N�g���N���X
class GameObjectManager : public GameObject
{
private:
	std::vector<GameObject*> create_objects;
	std::vector<GameObject*> destroy_objects;
	std::vector<GameObject*> game_objects_list;

	static GameObjectManager* instance;

public:
	GameObjectManager();
	virtual ~GameObjectManager();

public:
	void CheckCreateObject();
	void CheckDestroyObject();
	void CheckCollision(GameObject* target, GameObject* partner);
	void Draw(const Vector2D& screen_offset) const;
	virtual void Update(float screen_offset);
	std::vector<GameObject*>GetObjectsList() const;
	static GameObjectManager* GetInstance();

	template<class T>
	T* CreateGameObject(const Vector2D& generate_location)
	{
		// ��������Q�[���I�u�W�F�N�g�N���X�𓮓I�m��
		T* new_instance = new T();
		// GameObjectBase���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);
		// �G���[�`�F�b�N
		if (new_object == nullptr)
		{
			// ���I�m�ۂ����������̊J��
			delete new_instance;
			// ��O�e�L�X�g��ʒm
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
			return nullptr;
		}
		// �V�[�����̐ݒ�
		//new_object->SetOwnerScene(this);
		// �I�u�W�F�N�g�̏�����
		new_object->Initialize();
		// �ʒu���̐ݒ�
		new_object->SetLocation(generate_location);
		// �����I�u�W�F�N�g���X�g�̖����Ɋi�[����
		create_objects.push_back(new_object);
		// ���������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
		return new_instance;
	}

	/// <summary>
	/// �I�u�W�F�N�g�j������
	/// </summary>
	/// <param name="target">�j�����s���Q�[���I�u�W�F�N�g�̃|�C���^</param>
	void DestroyGameObject(GameObjectManager* target)
	{
		// �k���|�`�F�b�N
		if (target == nullptr)
		{
			return;
		}

		// �j���I�u�W�F�N�g���X�g���ɂ���΁A�ǉ����Ȃ�
		for (GameObject* obj : destroy_objects)
		{
			if (obj == target)
			{
				return;
			}
		}

		// �j�����s���I�u�W�F�N�g���X�g�ɒǉ�����
		destroy_objects.push_back(target);
	}
};

