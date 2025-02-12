#include "Kinoko.h"
#include "DxLib.h"

#define D_GRAVITY (9.807f)     //�d�͉����x(m/ss)


Kinoko::Kinoko()
{
}

Kinoko::~Kinoko()
{
}

void Kinoko::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::Get();

	kinoko_animation = rm->GetImages("Resource/Images/Item/mushroom.png", 1, 1, 1, 32, 32);

	image = kinoko_animation[0];
	g_velocity = 0;
	velocity = Vector2D(5.0f, 0.0f);


	// �����蔻��̐ݒ�
	this->collision.is_blocking = true;
	this->collision.object_type = eObjectType::eItem;
	collision.box_size = 32.0f;
	this->collision.hit_object_type.push_back(eObjectType::ePlayer);
	this->collision.hit_object_type.push_back(eObjectType::eBlock);

	/*__super::Initialize();*/
}

void Kinoko::Update(float delta_second)
{
	Movement(delta_second);
}

void Kinoko::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
	DrawFormatString(200, 0, 0x000000, "x���W:%f", velocity.x);
}

void Kinoko::Finalize()
{
	gm->DestroyGameObject(this);
}

void Kinoko::OnHitCollision(GameObject* hit_object)
{
	Collision oc = hit_object->GetCollision();

	// ���������A�I�u�W�F�N�g���ǂ�������
	if (oc.object_type == eObjectType::eBlock /*|| oc.object_type == eObjectType::ePlayer*/)
	{
		Vector2D diff;
		Vector2D dis;
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//�v���C���[�̉E���ƃI�u�W�F�N�g�̍���̔���
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);

				//�����߂�
				if (diff.x <= diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
				}
			}
			else
			{
				//�v���C���[�̉E��ƃI�u�W�F�N�g�̍����̔���
				diff = Vector2D((this->location.x + collision.box_size.x / 2), (this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - oc.box_size.x / 2), (hit_object->GetLocation().y + oc.box_size.y / 2));

				//�����߂�
				if (diff.x < diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
				}

			}
		}
		else
		{
			if (dis.y >= 0)
			{
				//�v���C���[�̍���ƃI�u�W�F�N�g�̉E���̔���
				diff = (this->location - collision.box_size / 2) - (hit_object->GetLocation() + oc.box_size / 2);

				//�����߂�
				if (-diff.x < -diff.y || dis.y == 0)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
				}
			}
			else
			{
				//�v���C���[�̍����ƃI�u�W�F�N�g�̉E��̔���
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
				}
			}
		}
	}
	// ���������I�u�W�F�N�g���v���C���[��������A�폜����
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		Finalize();
	}
}

void Kinoko::Movement(float delta_second)
{
	//�d�͑��x�̌v�Z
	g_velocity = D_GRAVITY / 444.0f;

	velocity.y += g_velocity;

	//�ړ��̎��s
	location += velocity * ITEM_SPEED * delta_second;

}
