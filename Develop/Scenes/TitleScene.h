#pragma once

#include "SceneBase.h"

// �^�C�g���V�[��
class TitleScene : public SceneBase
{
private:

	int back_ground_image;      // �^�C�g���̔w�i�摜
	int ui_time;                // ��ʉE��̐������ԕ`��iTIME�j
	int ui_world;               // ��ʉE��̐������Ԃ̍����ɂ��錻�݃}�b�v�̕`��iWORLD 1-1�j
	//int ui_coin_1_score;          // ��ʍ���̃}���I�X�R�A�̉E���ɂ���l�������R�C�������̕`��i �~ 00�j
	int ui_mario_score;         // ��ʍ���̃}���I�X�R�A�̕`��iMARIO 000000�j
	int ui_1_player;            // ��ʒ����������̃v���C���[�l���I���̕`��i�P PLAYER GAME�j
	int ui_top_score;           // ��ʒ������A�v���C���[�l���I���̉����ɂ���n�C�X�R�A�̕`��iTOP- 000000�j
	std::vector<int>ui_coin_1_score;          // ��ʍ���̃}���I�X�R�A�̉E���ɂ���l�������R�C�������̕`��i �~ 00�j

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;
};

