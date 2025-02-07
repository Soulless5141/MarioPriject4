#include "Kinoko.h"

#define D_GRAVITY (9.807f)     //重力加速度(m/ss)


Kinoko::Kinoko()
{
}

Kinoko::~Kinoko()
{
}

void Kinoko::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::Get();

	kinoko_animation = rm->GetImages("Resource/Images/Item/mushroom.png", 1, 1, 1, 32, 32);

	image = kinoko_animation[0];
	g_velocity = 0;
	velocity = Vector2D(5.0);

	// 当たり判定の設定
	this->collision.is_blocking = true;
	this->collision.object_type = eObjectType::eItem;
	this->collision.hit_object_type.push_back(eObjectType::ePlayer);
	this->collision.hit_object_type.push_back(eObjectType::eBlock);

	/*__super::Initialize();*/
}

void Kinoko::Update(float delta_second)
{
	Movement(delta_second);
}

void Kinoko::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Kinoko::Finalize()
{
}

void Kinoko::OnHitCollision(GameObject* hit_object)
{
	Collision oc = hit_object->GetCollision();

	// 当たった、オブジェクトが壁だったら
	if (oc.object_type == eObjectType::eBlock)
	{
		Vector2D diff;
		Vector2D dis;
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//プレイヤーの右下とオブジェクトの左上の判定
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);

				//押し戻し
				if (diff.x <= diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
			else
			{
				//プレイヤーの右上とオブジェクトの左下の判定
				diff = Vector2D((this->location.x + collision.box_size.x / 2), (this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - oc.box_size.x / 2), (hit_object->GetLocation().y + oc.box_size.y / 2));

				//押し戻し
				if (diff.x < diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity = 0.0f;
				}

			}
		}
		else
		{
			if (dis.y >= 0)
			{
				//プレイヤーの左上とオブジェクトの右下の判定
				diff = (this->location - collision.box_size / 2) - (hit_object->GetLocation() + oc.box_size / 2);

				//押し戻し
				if (-diff.x < -diff.y || dis.y == 0)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
				}
			}
			else
			{
				//プレイヤーの左下とオブジェクトの右上の判定
				diff = Vector2D((this->location.x - collision.box_size.x / 2), (this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + oc.box_size.x / 2), (hit_object->GetLocation().y - oc.box_size.y / 2));

				//押し戻し
				if (-diff.x < diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
		}
	}
}

void Kinoko::Movement(float delta_second)
{
	//重力速度の計算
	g_velocity = D_GRAVITY / 444.0f;

	velocity.y += g_velocity;

	//移動の実行
	location += velocity * ITEM_SPEED * delta_second;
}
