#pragma once
#include "../../Objects/GameObject.h"
#include "../../Objects/GameObjectManager.h"
#include "../Character/Player/Player.h"

#define ITEM_SPEED (20)

class ItemBase : public GameObject
{
private:
	Player* player;

protected:
	GameObjectManager* gm = GameObjectManager::Get();

	Vector2D velocity = Vector2D(0.0f);

public:
	

	ItemBase();
	virtual ~ItemBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

};

