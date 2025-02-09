#include "Stairs.h"

void Stairs::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::Get();
	image = rm->GetImages("Resource/Images/Block/kai_block.png",1,1,1,32,32)[0];

	// �����蔻��̐ݒ�
	collision.box_size = 32.0f;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

void Stairs::Draw(const Vector2D& screen_offset) const
{
	/*Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	back_ground_stage = rm->GetImages("Resource/Images/sora.png", 1, 1, 1, 32, 32)[0];
	DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_stage, TRUE);*/
	__super::Draw(screen_offset);
}

void Stairs::OnHitCollision(GameObject* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::eBlock)
	{
		//// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		//Collision hc = hit_object->GetCollision();
		//hc.point[0] += hit_object->GetLocation();
		//hc.point[1] += hit_object->GetLocation();

		//// �ŋߖT�_�����߂�
		//Vector2D near_point = CheckCollision(hc, this->location);

		//// Player����near_point�ւ̕����x�N�g�����擾
		//Vector2D dv2 = near_point - this->location;
		//Vector2D dv = this->location - near_point;

		//// �߂荞�񂾍���
		//float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//// diff�̕������߂�
		//location += dv.Normalize() * diff;
	}
}