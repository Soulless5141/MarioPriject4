#pragma once

#include "../Objects/GameObjectManager.h"
#include <vector>
#include <string>

/// <summary>
/// �V�[���^�C�v
/// </summary>
enum class eSceneType
{
	title,
	in_game,
	re_start,
	result,
	exit,
};

/// <summary>
/// �V�[�����N���X
/// </summary>
class SceneBase
{
public:
	GameObjectManager* gm = GameObjectManager::Get();
	Vector2D	screen_offset;	// �X�N���[���I�t�Z�b�g
	std::vector<GameObject*> game_objects_list;

public:
	SceneBase() :
		screen_offset(0.0f)
	{

	}
	virtual ~SceneBase()
	{
		// ����Y��h�~
		Finalize();
	}

public:
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()
	{
		screen_offset.y = 16.0f;
	}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns>���̃V�[���^�C�v���</returns>
	virtual eSceneType Update(const float& delta_second)
	{
		// ��������I�u�W�F�N�g������΁A�I�u�W�F�N�g���X�g���ɑ}������
		
		gm->CheckCreateObject();

		gm->CheckDestroyObject();

		game_objects_list = gm->GetObjectsList();

		// ���X�g���̃I�u�W�F�N�g���X�V����
		for (GameObject* obj : game_objects_list)
		{
			obj->Update(delta_second);
		}

		// �����蔻��m�F����
		for (int i = 0; i < game_objects_list.size(); i++)
		{
			if (eMobilityType::Stationary == game_objects_list[i]->GetMobility())
			{
				continue;
			}

			for (int j = 0; j < game_objects_list.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				CheckCollision(game_objects_list[i], game_objects_list[j]);
			}
		}

		// ���݂̃V�[������ԋp����
		return GetNowSceneType();
	}

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw()
	{
		game_objects_list = gm->GetObjectsList();
		// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`�悷��
		for (GameObject* obj : game_objects_list)
		{
			obj->Draw(screen_offset);
		}
	}

	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize()
	{

	}

	/// <summary>
	/// ���݂̃V�[���^�C�v�擾����
	/// </summary>
	/// <returns>���݂̃V�[���^�C�v���</returns>
	virtual const eSceneType GetNowSceneType() const = 0;

	/// <summary>
	/// �����蔻��m�F����
	/// </summary>
	/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
	/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
	virtual void CheckCollision(GameObject* target, GameObject* partner)
	{
	}

public:


	/// <summary>
	/// �X�N���[���I�t�Z�b�g���擾����
	/// </summary>
	/// <returns>�X�N���[���I�t�Z�b�g�l</returns>
	const Vector2D GetScreenOffset() const
	{
		return screen_offset;
	}
};
