#include "Nokonoko.h"
/// <summary>
/// ����������
/// </summary>
void Nokonoko::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	animation = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	image = animation[0];

	collision.is_blocking = true;
	collision.box_size = Vector2D(64.0f,32.0f);
	collision.pivot = location;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	location.y -= collision.box_size.y/2;
}
/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Nokonoko::Update(float delta_second)
{

}
/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Nokonoko::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}
/// <summary>
/// ���쏈��
/// </summary>
/// <param name="delta_second"></param>
void Nokonoko::Movement(float delta_second)
{

}
/// <summary>
/// �I������
/// </summary>
void Nokonoko::Finalize()
{

}
/// <summary>
/// �����蔻�菈��
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void Nokonoko::OnHitCollision(GameObject* object)
{

}
/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Nokonoko::AnimationControl(float delta_second)
{

}