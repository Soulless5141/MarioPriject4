#pragma once

#include "../../../Objects/GameObject.h"
#include "../Enemy/EnemyBase.h"
#include "State/Enum/PlayerState.h"

#define FRICTION (3.612)		//���C��

// �v���C���[���
enum ePlayerMode
{
	DEKAMARIO,		// �ł����
	FAIYAMARIO,		// �t�@�C�A���
	MARIO,			// ���у}���I���
	STARMARIO,		// �ł�Star���
	STARSMALLMARIO,	// ����Star���
};

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public GameObject
{
private:
	std::vector<int> dekamarimation_animation;		// �ړ��̃A�j���[�V�����摜
	std::vector<int> dekamario_animation;		// ���S�̃A�j���[�V�����摜
	std::vector<int> faiyamario_animation;		// �W�����v�̃A�j���[�V�����摜
	std::vector<int> mario_animation;		// ���Ⴊ�񂾎��̃A�j���[�V�����摜
	std::vector<int> starmario_animation;		// �S�[���������̃A�j���[�V�����摜

	std::vector<int> starsmallmario_animation;

	ePlayerMode player_mode;				// �v���C���[���
	ePlayerState player_state;
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
	float move_time;
	const int animation_num[4] = { 1,2,3,2 };
	float power_upanddown_time;						// �p���[�A�b�v����

private:
	class PlayerStateBase* state = nullptr;
	float g_velocity = 0.0f;

public:
	Vector2D velocity = Vector2D(0.0f);
	Vector2D box_size = Vector2D(0.0f);
	float f_velocity = 0.0f;				//�������x
	bool is_fly;							//�󒆂ɂ��邩�ǂ���
	float damage_time;						//�_���[�W���󂯂��ۖ��G�ɂȂ��Ă��鎞��
                                   

public:
	int sound;
	class EnemyBase* enemy;					// �G�l�~�[�̏�Ԋm�F

public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

public:

	/// <summary>
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	ePlayerMode GetPlayerMode() const;

	/// <summary>
	/// �v���C���[�̌��݌`�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̌��݌`��</returns>
	ePlayerState GetPlayerState() const;

	void SetDefoltX();

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);

	/// <summary>
	/// �p���[�A�b�v���̃A�j���[�V��������
	/// </summary>
	/// <param name="delta_second"></param>
	void PowerUpAnim(float delta_second);

	/// <summary>
	/// power�_�E�����̃A�j���[�V��������
	/// </summary>
	/// <param name="delta_second"></param>
	void PowerDownAnim(float delta_second);

public:
	/// <summary>
	///����State��ݒ� 
	/// </summary>
	/// <param name="next_state">����State</param>
	void SetNextState(ePlayerState next_state);

	/// <summary>
	///���W�̎擾
	/// </summary>
	Vector2D& GetLocation();

	void SetReverse(bool TF);

	float GetPowerUpTime();
};
