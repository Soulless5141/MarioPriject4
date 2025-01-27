#pragma once

#include "../../Utility/Vector2D.h"

/// <summary>
/// �����̎��
/// </summary>
enum eMobilityType
{
	Stationary,		// �Œ�
	Movable,		// ��
};

class HaikeiBase
{
protected:
	class SceneBase* owner_scene;	// ���L����V�[�����
	Vector2D			location;		// �ʒu���W
	int					image;			// �摜���
	int					z_layer;		// ���C���[���
	eMobilityType		mobility;		// ����

public:
	HaikeiBase();
	virtual ~HaikeiBase();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset">�I�t�Z�b�g�l</param>
	virtual void Draw(const Vector2D& screen_offset) const;
	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize();

public:
	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(HaikeiBase* hit_object);

public:
	/// <summary>
	/// ���L�V�[�����̐ݒ�
	/// </summary>
	/// <param name="scene">���L�V�[�����</param>
	void SetOwnerScene(class SceneBase* scene);

	/// <summary>
	/// �ʒu���W�擾����
	/// </summary>
	/// <returns>�ʒu���W���</returns>
	const Vector2D& GetLocation() const;

	/// <summary>
	/// �ʒu���ύX����
	/// </summary>
	/// <param name="location">�ύX�������ʒu���</param>
	void SetLocation(const Vector2D& location);

	/// <summary>
	/// �y���C���[���擾����
	/// </summary>
	/// <returns>�y���C���[���</returns>
	const int GetZLayer() const;

	/// <summary>
	/// �������̎擾����
	/// </summary>
	/// <returns>�������</returns>
	const eMobilityType GetMobility() const;
};

