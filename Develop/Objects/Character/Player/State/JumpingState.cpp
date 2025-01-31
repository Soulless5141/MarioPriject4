#include "JumpingState.h"

#include "DxLib.h"
#include "../../../../Utility/InputManager.h"
#include "../Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[���</param>
JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
JumpingState::~JumpingState()
{

}

/// <summary>
/// ����������
/// </summary>
void JumpingState::Initialize()
{
	if (this->player->velocity.y == 0)
	{
		this->player->velocity.y -= 12.0f; //�W�����v��
	}
	
	ResourceManager* rm = ResourceManager::Get();
	this->player->sound = rm->GetSounds("Resource/Sounds/SE_SuperJump.wav");
}

/// <summary>
/// �I������
/// </summary>
void JumpingState::Finalize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void JumpingState::Update()
{
	//���E���͂�����Ȃ�
	InputManager* input = InputManager::Get();

	//�n�ʂɐG�ꂽ��
	if (player->velocity.y >= 0)
	{
		//���E���͂�����Ȃ�
		InputManager* input = InputManager::Get();

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
void JumpingState::Draw() const
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
ePlayerState JumpingState::GetState() const
{
	return ePlayerState::eJump;
}

