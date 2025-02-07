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

	__super::Initialize();
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
}

void Kinoko::Movement(float delta_second)
{
	//重力速度の計算
	g_velocity = D_GRAVITY / 444.0f;

	velocity.y += g_velocity;

	//移動の実行
	location.x += velocity.x * ITEM_SPEED * delta_second;
}
