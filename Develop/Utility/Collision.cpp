#include "Collision.h"
#include <math.h>

/// <summary>
/// �K�p�I�u�W�F�N�g���m�F���鏈��
/// </summary>
/// <param name="hit_object">����̃I�u�W�F�N�g�^�C�v</param>
/// <returns>�K�p����I�u�W�F�N�g�Ȃ�Atrue</returns>
bool Collision::IsCheckHitTarget(eObjectType hit_object) const
{
	// �K�p����I�u�W�F�N�g�^�C�v�Ȃ�Atrue
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="c1">���1</param>
/// <param name="c2">���2</param>
/// <returns>�������Ă���Ȃ�Atrue</returns>
bool IsCheckCollision(const Collision& c1, const Collision& c2)
{
	// ��`A�̍��ӂƋ�`B�̉E�ӂ̊֌W�`�F�b�N
	bool is_left_less_right = false;
	if (c1.pivot.x - (c1.box_size.x / 2) <= c2.pivot.x + (c2.box_size.x / 2))
	{
		is_left_less_right = true;
	}

	// ��`A�̉E�ӂƋ�`B�̍��ӂ̊֌W�`�F�b�N
	bool is_right_greater_left = false;
	if (c1.pivot.x + (c1.box_size.x / 2) <= c2.pivot.x - (c2.box_size.x / 2))
	{
		is_right_greater_left = true;
	}

	// ��`A�̏�ӂƋ�`B�̉��ӂ̊֌W�`�F�b�N
	bool is_top_less_bottom = false;
	if (c1.pivot.y - (c1.box_size.y / 2) <= c2.pivot.y + (c2.box_size.y / 2))
	{
		is_top_less_bottom = true;
	}

	// ��`A�̉��ӂƋ�`B�̏�ӂ̊֌W�`�F�b�N
	bool is_bottom_greater_top = false;
	if (c1.pivot.y + (c1.box_size.y / 2) <= c2.pivot.y - (c2.box_size.y / 2))
	{
		is_bottom_greater_top = true;
	}

	// �e�ӂ̊֌W���`�F�b�N����(�S��true�Ȃ瓖����)
	if (is_left_less_right == true &&
		is_right_greater_left == true &&
		is_top_less_bottom == true &&
		is_bottom_greater_top)
	{
		return true;
	}

	// �S�Ă̏������������Ă��Ȃ��ꍇ�A�������Ă��Ȃ�
	return false;
}
