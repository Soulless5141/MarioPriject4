#pragma once
#include "BlockBase.h"

class Goal : public BlockBase
{
public:
	Goal() = default;
	~Goal() {

	}

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void SetImages();
};

