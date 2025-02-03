#pragma once
#pragma once
#include "PlayerStateBase.h"
#include "../../../../Utility/Vector2D.h"

/// <summary>
/// �W�����v���
/// </summary>
class SquatState : public PlayerStateBase
{
private:
	//�O�t���[���̍��W���


public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="p">�v���C���[���</param>
	SquatState(class Player* p);

	//�f�X�g���N�^
	virtual ~SquatState();

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

