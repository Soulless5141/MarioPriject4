#include "kuribo.h"
/// <summary>
/// 初期化処理
/// </summary>
void kuribo::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = animation[0];
}
/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void kuribo::Update(float delta_second)
{

}
/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void kuribo::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}
/// <summary>
/// 動作処理
/// </summary>
/// <param name="delta_second"></param>
void kuribo::Movement(float delta_second)
{

}
/// <summary>
/// 終了処理
/// </summary>
void kuribo::Finalize()
{

}
/// <summary>
/// 当たり判定処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void kuribo::OnHitCollision(GameObject* object)
{

}
/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void kuribo::AnimationControl(float delta_second)
{

}