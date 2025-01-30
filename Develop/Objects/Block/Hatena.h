#pragma once
#include "BlockBase.h"

class Hatena : public BlockBase
{
private:
	std::vector<int> animation;
public:

	Hatena() = default;
	virtual ~Hatena()
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

