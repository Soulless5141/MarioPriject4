#include "Stairs.h"

void Stairs::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	image = rm->GetImages("Resource/Images/Block/kai_block.png",1,1,1,32,32)[0];

	// 当たり判定の設定
	collision.box_size = 32.0f;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

void Stairs::Draw(const Vector2D& screen_offset) const
{
	/*Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
	back_ground_stage = rm->GetImages("Resource/Images/sora.png", 1, 1, 1, 32, 32)[0];
	DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_stage, TRUE);*/
	__super::Draw(screen_offset);
}

void Stairs::OnHitCollision(GameObject* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::eBlock)
	{
		//// 当たり判定情報を取得して、カプセルがある位置を求める
		//Collision hc = hit_object->GetCollision();
		//hc.point[0] += hit_object->GetLocation();
		//hc.point[1] += hit_object->GetLocation();

		//// 最近傍点を求める
		//Vector2D near_point = CheckCollision(hc, this->location);

		//// Playerからnear_pointへの方向ベクトルを取得
		//Vector2D dv2 = near_point - this->location;
		//Vector2D dv = this->location - near_point;

		//// めり込んだ差分
		//float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//// diffの分だけ戻る
		//location += dv.Normalize() * diff;
	}
}