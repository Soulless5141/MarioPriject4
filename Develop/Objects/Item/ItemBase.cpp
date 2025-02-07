#include "ItemBase.h"

ItemBase::ItemBase()
{
}

ItemBase::~ItemBase()
{
	Finalize();
}

void ItemBase::Initialize()
{
	// “–‚½‚è”»’è‚ÌÝ’è
	this->collision.is_blocking = true;
	this->collision.object_type = eObjectType::eItem;
	this->collision.hit_object_type.push_back(eObjectType::ePlayer);
	this->collision.hit_object_type.push_back(eObjectType::eBlock);
}

void ItemBase::Update(float delta_second)
{
}

void ItemBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void ItemBase::Finalize()
{
}

void ItemBase::OnHitCollision(GameObject* hit_object)
{
	
}
