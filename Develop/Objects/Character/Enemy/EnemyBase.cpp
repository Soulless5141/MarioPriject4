#include "EnemyBase.h"

/// <summary>
/// 初期化処理
/// </summary>
void EnemyBase::Initialize()
{

}
/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void EnemyBase::Update(float delta_second)
{

}
/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}
/// <summary>
/// 動作処理
/// </summary>
/// <param name="delta_second"></param>
void EnemyBase::Movement(float delta_second)
{

}
/// <summary>
/// 終了処理
/// </summary>
void EnemyBase::Finalize()
{

}
/// <summary>
/// 当たり判定処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void EnemyBase::OnHitCollision(GameObject* object)
{

}
/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void EnemyBase::AnimationControl(float delta_second)
{

}