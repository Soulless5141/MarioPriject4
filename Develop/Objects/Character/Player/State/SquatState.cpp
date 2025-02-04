#include "SquatState.h"

#include "DxLib.h"
#include "../../../../Utility/InputManager.h"
#include "../Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[���</param>
SquatState::SquatState(class Player* p)
	: PlayerStateBase(p)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SquatState::~SquatState()
{

}

/// <summary>
/// ����������
/// </summary>
void SquatState::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
}

/// <summary>
/// �I������
/// </summary>
void SquatState::Finalize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void SquatState::Update()
{
	//���E���͂�����Ȃ�
	InputManager* input = InputManager::Get();

	//�n�ʂɐG�ꂽ��
	if (player->velocity.y >= 0)
	{
		//���E���͂�����Ȃ�
		InputManager* input = InputManager::Get();

		if (input->GetKey(KEY_INPUT_S))
		{
			
		}

		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::eIdle);
	}
	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	{
		//�ړ���ԂɑJ��
		player->SetNextState(ePlayerState::eRun);
	}

}

/// <summary>
/// �`�揈��
/// </summary>
void SquatState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	/*DrawBox(x, y, x + (int)(player->box_size.x), y + (int)(player->box_size.y),
		GetColor(0, 0, 255), FALSE);*/
}

/// <summary>
/// ���݂̃X�e�[�g�����擾����
/// </summary>
/// <returns>���݂̃X�e�[�g���</returns>
ePlayerState SquatState::GetState() const
{
	return ePlayerState::eSquat;
}

