#include "Nokonoko.h"
/// <summary>
/// 初期化処理
/// </summary>
void Nokonoko::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	animation = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	image = animation[0];

	collision.is_blocking = true;
	collision.box_size = Vector2D(64.0f,32.0f);
	collision.pivot = location;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	location.y -= collision.box_size.y/2;
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