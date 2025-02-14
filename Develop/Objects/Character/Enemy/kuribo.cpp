#include "kuribo.h"
/// <summary>
/// 初期化処理
/// </summary>
void kuribo::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = animation[0];

	velocity = Vector2D(-4.0f, 0.0f);

	collision.is_blocking = true;
	collision.box_size = 32.0f;
	collision.pivot = location;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	/*collision.hit_object_type.push_back(eObjectType::eEnemy);*/
}
/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void kuribo::Update(float delta_second)
{
	Movement(delta_second);

	AnimationControl(delta_second);
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
	if (die == false)
	{
		//重力速度の計算
		g_velocity = D_GRAVITY / 444.0f;

		velocity.y += g_velocity;

		//移動の実行
		location += velocity * ENEMY_SPEED * delta_second;
	}
}
/// <summary>
/// 終了処理
/// </summary>
void kuribo::Finalize()
{
	gm->DestroyGameObject(this);
}
/// <summary>
/// 当たり判定処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void kuribo::OnHitCollision(GameObject* hit_object)
{
	Collision oc = hit_object->GetCollision();
	Vector2D diff;
	Vector2D dis;

	// 当たった、オブジェクトが壁だったら
	if ((oc.object_type == eObjectType::eBlock) &&
		collision.object_type == eObjectType::eEnemy)
	{
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//エネミーの右下とオブジェクトの左上の判定
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);

				//押し戻し
				if (diff.x <= diff.y)
				{
					location.x -= diff.x;
					velocity.x *= -1;
				}
				else
				{
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
			else
			{
				//エネミーの右上とオブジェクトの左下の判定
				diff = Vector2D((this->location.x + collision.box_size.x / 2), (this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - oc.box_size.x / 2), (hit_object->GetLocation().y + oc.box_size.y / 2));

				//押し戻し
				if (diff.x > diff.y && diff.x != 0.0f)
				{
					location.x -= diff.x;
					velocity.x *= -1;
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
				//エネミーの左上とオブジェクトの右下の判定
				diff = (this->location - collision.box_size / 2) - (hit_object->GetLocation() + oc.box_size / 2);

				//押し戻し
				if (-diff.x < -diff.y || dis.y == 0)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity = 0.0f;
				}
			}
			else
			{
				//エネミーの左下とオブジェクトの右上の判定
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

	/*if (collision.object_type == eObjectType::eEnemy)
	{
		if (oc.object_type == eObjectType::ePlayer)
		{
			die = true;
			animation_count = 0;
			this->collision.object_type = eObjectType::eNone;
		}
	}*/
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void kuribo::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		//死んでいるか判定して画像替え
		if (die == false)
		{
			if (animation_count >= 3)
			{
				animation_count = 0;
				// 画像の設定
				if (image == animation[0])
				{
					image = animation[1];
				}
				else
				{
					image = animation[0];
				}
			}
		}
		else
		{
			image = animation[2];
			animation_count++;
			if (animation_count >= 15)
			{
				Finalize();
			}
		}
	}
}
