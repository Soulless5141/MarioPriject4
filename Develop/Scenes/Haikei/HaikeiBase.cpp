#include "HaikeiBase.h"
#include "../SceneManager.h"
#include "DxLib.h"

HaikeiBase::HaikeiBase() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	mobility(eMobilityType::Stationary)
{

}

HaikeiBase::~HaikeiBase()
{

}

/// <summary>
/// ����������
/// </summary>
void HaikeiBase::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void HaikeiBase::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void HaikeiBase::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

/// <summary>
/// �I��������
/// </summary>
void HaikeiBase::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void HaikeiBase::OnHitCollision(HaikeiBase* hit_object)
{

}

/// <summary>
/// ���L�V�[�����̐ݒ�
/// </summary>
/// <param name="scene">���L�V�[�����</param>
void HaikeiBase::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

/// <summary>
/// �ʒu���W�擾����
/// </summary>
/// <returns>�ʒu���W���</returns>
const Vector2D& HaikeiBase::GetLocation() const
{
	return location;
}

/// <summary>
/// �ʒu���ύX����
/// </summary>
/// <param name="location">�ύX�������ʒu���</param>
void HaikeiBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

/// <summary>
/// Z���C���[���擾����
/// </summary>
/// <returns>Z���C���[���</returns>
const int HaikeiBase::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// �������̎擾����
/// </summary>
/// <returns>�������</returns>
const eMobilityType HaikeiBase::GetMobility() const
{
	return mobility;
}
