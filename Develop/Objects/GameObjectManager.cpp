#include "GameObjectManager.h"
#include "../Scenes/SceneBase.h"
#include <vector>
#include "DxLib.h"

// �ÓI�����o�ϐ���`
GameObjectManager* GameObjectManager::instance = nullptr;	// ���N���X�̃|�C���^

GameObjectManager::GameObjectManager() :
	create_objects(),
	destroy_objects(),
	game_objects_list()
{

}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::CheckCreateObject()
{
	// ��������I�u�W�F�N�g������΁A�I�u�W�F�N�g���X�g���ɑ}������
	if (!create_objects.empty())
	{
		for (GameObject* obj : create_objects)
		{
			// ���C���[������ɏ��Ԃ����ւ���
			int z_layer = obj->GetZLayer();
			std::vector<GameObject*>::iterator itr = game_objects_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
			// ���X�g�̖����ɂȂ�܂ő�������
			for (; itr != game_objects_list.end(); itr++)
			{
				// Z���C���[���傫���ꏊ�ɗv�f��ǉ�����
				// �� itr->ZLayer{1, 1, 2, 3}�Az_layer = 2 �̎�
				//    itr->ZLayer{1, 1, 2, z_layer, 3}�Ƃ���
				if (z_layer < (*itr)->GetZLayer())
				{
					break;
				}
			}
			// ���X�g�̓r���ɑ}������
			game_objects_list.insert(itr, obj);
		}
		// �������X�g���������
		create_objects.clear();
	}
}

void GameObjectManager::CheckDestroyObject()
{
	if (!destroy_objects.empty())
	{
		for (GameObject* obj : destroy_objects)
		{
			std::vector<GameObject*>::iterator itr = game_objects_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
			// ���X�g�̖����ɂȂ�܂ő�������
			for (; itr != game_objects_list.end(); itr++)
			{
				// ���X�g���ɂ���΁A�폜����
				if ((*itr) == obj)
				{
					game_objects_list.erase(itr);
					obj->Finalize();
					delete obj;
					break;
				}
			}
		}
		// ���I�z��̊J��
		destroy_objects.clear();
	}
}

void GameObjectManager::CheckCollision(GameObject* target, GameObject* partner)
{
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// �����̎n�_�ƏI�_��ݒ肷��
		tc.point[0] += target->GetLocation() - 32;
		tc.point[1] += target->GetLocation() + 32;
		pc.point[0] += partner->GetLocation() - 32;
		pc.point[1] += partner->GetLocation() + 32;

		// �J�v�Z�����m�̓����蔻��
		if (IsCheckCollision(tc, pc))
		{
			// �������Ă��邱�Ƃ�ʒm����
			partner->OnHitCollision(target);
			target->OnHitCollision(partner);

		}
	}
}

std::vector<GameObject*>GameObjectManager::GetObjectsList() const
{
	return game_objects_list;
}

GameObjectManager* GameObjectManager::GetInstance()
{
	// �C���X�^���X����������Ă��Ȃ��ꍇ�A��������
	if (instance == nullptr)
	{
		instance = new GameObjectManager();
	}

	return instance;
}