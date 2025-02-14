#pragma once
#include"SceneBase.h"
#include"../Objects/Character/Player/Player.h"
#include "../Utility/Camera.h"

#define BLOCK_MAX_X (211)
#define BLOCK_MAX_Y (15)

class InGameScene : public SceneBase
{
private:
	class Player* player;		// �v���C���[���
	Camera* camera;
	int back_ground_stage;		// �w�i�摜
	int ground_stage;		// �w�i�摜
	int back_bgm;		// �w�i�摜
	bool pause_flag;			// �ꎞ��~�t���O

	int ui_time;                // ��ʉE��̐������ԕ`��iTIME�j400�X�^�[�g�Ō����Ă���
	int ui_world;               // ��ʉE��̐������Ԃ̍����ɂ��錻�݃}�b�v�̕`��iWORLD 1-1�j
	//int ui_coin_1_score;          // ��ʍ���̃}���I�X�R�A�̉E���ɂ���l�������R�C�������̕`��i �~ 00�j
	int ui_mario_score;         // ��ʍ���̃}���I�X�R�A�̕`��iMARIO 000000�j
	std::vector<int>ui_coin_1_score;          // ��ʍ���̃}���I�X�R�A�̉E���ɂ���l�������R�C�������̕`��i �~ 00�j

	std::vector<std::vector<int>>haikei_block;
	std::vector<std::vector<int>>block;
	std::vector<std::vector<GameObject*>>object;
	std::vector<int>ui_num;

	//// �w�i�摜�̓ǂݍ���
	//ResourceManager* rm = ResourceManager::GetInstance();
	//GameObjectManager* gm = GameObjectManager::GetInstance();

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize() override;	

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

	/// <summary>
	/// �����蔻��m�F����
	/// </summary>
	/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
	/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	/// <summary>
	/// �X�e�[�W�}�b�v�i�ǁj�ǂݍ��ݏ���
	/// </summary>
	void LoadStageMapCSV();
	/// <summary>
	/// �X�e�[�W�}�b�v�ǂݍ��ݏ���
	/// </summary>
	void LoadBackStageMapCSV();
	/// <summary>
	/// �X�e�[�W����
	/// </summary>
	void CreateStage();
	/// <summary>
	/// �I�u�W�F�N�g�폜
	/// </summary>
	void DeleteStage();
};

