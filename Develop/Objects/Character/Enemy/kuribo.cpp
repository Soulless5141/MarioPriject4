#include "kuribo.h"
/// <summary>
/// ����������
/// </summary>
void kuribo::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = animation[0];
}
/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void kuribo::Update(float delta_second)
{

}
/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void kuribo::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}
/// <summary>
/// ���쏈��
/// </summary>
/// <param name="delta_second"></param>
void kuribo::Movement(float delta_second)
{

}
/// <summary>
/// �I������
/// </summary>
void kuribo::Finalize()
{

}
/// <summary>
/// �����蔻�菈��
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void kuribo::OnHitCollision(GameObject* object)
{

}
/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void kuribo::AnimationControl(float delta_second)
{

}