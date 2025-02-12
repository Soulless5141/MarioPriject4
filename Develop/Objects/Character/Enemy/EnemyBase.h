#pragma once

#include "../../../Objects/GameObject.h"
#include "../../../Objects/GameObjectManager.h"

#define ENEMY_SPEED (20)

class EnemyBase : public GameObject
{
protected:
	std::vector<int> animation;
	float g_velocity;
	Vector2D velocity = Vector2D(0.0f);

	GameObjectManager* gm = GameObjectManager::Get();

public:
	EnemyBase() = default;
	~EnemyBase()
	{

	}
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	virtual void Update(float delta_second) override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void Movement(float delta_second);
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize() override;
	/// <summary>
	/// 当たり判定処理
	/// </summary>
	/// <param name="object">当たったオブジェクト</param>
	virtual void OnHitCollision(GameObject* object) override;
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	virtual void AnimationControl(float delta_second);
};

