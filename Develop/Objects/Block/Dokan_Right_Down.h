#pragma once
#include "BlockBase.h"

class Dokan_Right_Down : public BlockBase
{
public:
	Dokan_Right_Down() = default;
	~Dokan_Right_Down()
	{

	}

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;
};

