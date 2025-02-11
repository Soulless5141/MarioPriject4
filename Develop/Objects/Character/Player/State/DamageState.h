#pragma once
#include "PlayerStateBase.h"
#include "../../../../Utility/Vector2D.h"

/// <summary>
/// �_���[�W���
/// </summary>
class DamageState : public PlayerStateBase
{
private:
	float accel_force;
	//���͏��
	class InputManager* input;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="p">�v���C���[���</param>
	DamageState(class Player* p);

	//�f�X�g���N�^
	virtual ~DamageState();

public:
	//�����������֐�
	virtual void Initialize() override;

	//�I�������֐�
	virtual void Finalize() override;

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() const override;

	//��Ԃ̎擾
	virtual ePlayerState GetState() const override;
};

