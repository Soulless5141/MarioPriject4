#include "Kinoko.h"

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

	__super::Initialize();
}

void Kinoko::Update(float delta_second)
{
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
}

void Kinoko::AnimationControl(float delta_second)
{
}
