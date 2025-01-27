#include "BlockBase.h"

BlockBase::BlockBase()
{

}

BlockBase::~BlockBase()
{

}

void BlockBase::Initialize()
{

}

void BlockBase::Update(float delta_second)
{

}

void BlockBase::OnHitCollision(GameObject* object)
{


	player->velocity.x = 0;
}