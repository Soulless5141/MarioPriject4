#include "Nokonoko.h"
/// <summary>
/// 初期化処理
/// </summary>
void Nokonoko::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	animation = rm->GetImages("Resource/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	image = animation[0];
}
/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void Nokonoko::Update(float delta_second)
{

}
/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Nokonoko::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}
/// <summary>
/// 動作処理
/// </summary>
/// <param name="delta_second"></param>
void Nokonoko::Movement(float delta_second)
{

}
/// <summary>
/// 終了処理
/// </summary>
void Nokonoko::Finalize()
{

}
/// <summary>
/// 当たり判定処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void Nokonoko::OnHitCollision(GameObject* object)
{

}
/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void Nokonoko::AnimationControl(float delta_second)
{

}