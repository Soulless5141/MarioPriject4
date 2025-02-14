#include "kuribo.h"
/// <summary>
/// ����������
/// </summary>
void kuribo::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = animation[0];

	velocity = Vector2D(-4.0f, 0.0f);

	collision.is_blocking = true;
	collision.box_size = 32.0f;
	collision.pivot = location;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	/*collision.hit_object_type.push_back(eObjectType::eEnemy);*/
}
/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void kuribo::Update(float delta_second)
{
	Movement(delta_second);

	AnimationControl(delta_second);
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
	if (die == false)
	{
		//�d�͑��x�̌v�Z
		g_velocity = D_GRAVITY / 444.0f;

		velocity.y += g_velocity;

		//�ړ��̎��s
		location += velocity * ENEMY_SPEED * delta_second;
	}
}
/// <summary>
/// �I������
/// </summary>
void kuribo::Finalize()
{
	gm->DestroyGameObject(this);
}
/// <summary>
/// �����蔻�菈��
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void kuribo::OnHitCollision(GameObject* hit_object)
{
	Collision oc = hit_object->GetCollision();
	Vector2D diff;
	Vector2D dis;

	// ���������A�I�u�W�F�N�g���ǂ�������
	if ((oc.object_type == eObjectType::eBlock) &&
		collision.object_type == eObjectType::eEnemy)
	{
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//�G�l�~�[�̉E���ƃI�u�W�F�N�g�̍���̔���
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);

				//�����߂�
				if (diff.x <= diff.y)
				{
					location.x -= diff.x;
					velocity.x *= -1;
				}
				else
				{
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
			else
			{
				//�G�l�~�[�̉E��ƃI�u�W�F�N�g�̍����̔���
				diff = Vector2D((this->location.x + collision.box_size.x / 2), (this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - oc.box_size.x / 2), (hit_object->GetLocation().y + oc.box_size.y / 2));

				//�����߂�
				if (diff.x > diff.y && diff.x != 0.0f)
				{
					location.x -= diff.x;
					velocity.x *= -1;
				}
				else
				{
					location.y -= diff.y;
					velocity = 0.0f;
				}

			}
		}
		else
		{
			if (dis.y >= 0)
			{
				//�G�l�~�[�̍���ƃI�u�W�F�N�g�̉E���̔���
				diff = (this->location - collision.box_size / 2) - (hit_object->GetLocation() + oc.box_size / 2);

				//�����߂�
				if (-diff.x < -diff.y || dis.y == 0)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity = 0.0f;
				}
			}
			else
			{
				//�G�l�~�[�̍����ƃI�u�W�F�N�g�̉E��̔���
				diff = Vector2D((this->location.x - collision.box_size.x / 2), (this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + oc.box_size.x / 2), (hit_object->GetLocation().y - oc.box_size.y / 2));

				//�����߂�
				if (-diff.x < diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
		}
	}

	/*if (collision.object_type == eObjectType::eEnemy)
	{
		if (oc.object_type == eObjectType::ePlayer)
		{
			die = true;
			animation_count = 0;
			this->collision.object_type = eObjectType::eNone;
		}
	}*/
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void kuribo::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		//����ł��邩���肵�ĉ摜�ւ�
		if (die == false)
		{
			if (animation_count >= 3)
			{
				animation_count = 0;
				// �摜�̐ݒ�
				if (image == animation[0])
				{
					image = animation[1];
				}
				else
				{
					image = animation[0];
				}
			}
		}
		else
		{
			image = animation[2];
			animation_count++;
			if (animation_count >= 15)
			{
				Finalize();
			}
		}
	}
}
