#pragma once
#include "BlockBase.h"

class Dokan_Left_Down : public BlockBase
{
public:
	Dokan_Left_Down() = default;
	~Dokan_Left_Down()
	{

	}

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object) override;
};

