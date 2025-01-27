#pragma once

#include "../GameObjectManager.h"

class Block : public GameObject
{
private:

public:
	Block();
	virtual ~Block();

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectManager* hit_object) ;

};

