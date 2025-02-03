#pragma once

#include "Vector2D.h"
#include <vector>

// �I�u�W�F�N�g�^�C�v
enum class eObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eBlock,
	eItem
};

// �����蔻����N���X
class Collision
{
public:
	bool						is_blocking;		// ���蔲���t���O
	eObjectType					object_type;		// ���g�̃I�u�W�F�N�g�^�C�v
	std::vector<eObjectType>	hit_object_type;	// �K�p����I�u�W�F�N�g�^�C�v
	Vector2D					pivot;				// ���S�_
	Vector2D					box_size;			// ����̑傫��

public:
	Collision() :
		is_blocking(false),
		object_type(eObjectType::eNone),
		hit_object_type(),
		pivot(0.0f),
		box_size(0.0f)
	{

	}
	~Collision()
	{
		hit_object_type.clear();
	}

	// �����蔻��L���m�F����
	bool IsCheckHitTarget(eObjectType hit_object) const;
};

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="c1">�`��̏��1</param>
/// <param name="c2">�`��̏��2</param>
/// <returns>�������Ă���Ȃ�Atrue</returns>
bool IsCheckCollision(const Collision& c1, const Collision& c2);


