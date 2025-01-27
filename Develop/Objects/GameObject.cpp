#include "GameObject.h"
#include "DxLib.h"

GameObject::GameObject() :
	reverse(false)
{

}

GameObject::~GameObject()
{

}

void GameObject::Initialize()
{
	
}

void GameObject::Update(float delta_second)
{

}

void GameObject::Draw(const Vector2D& screen_offset) const
{
	Camera* camera = Camera::Get();
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = camera->ConvertLcoationToScreen(this->location + screen_offset);
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE, reverse);
}

void GameObject::Finalize()
{

}

void GameObject::OnHitCollision(GameObject* object)
{

}

const Vector2D& GameObject::GetLocation() const
{
	return location;
}

void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

const Collision& GameObject::GetCollision() const
{
	return collision;
}

const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// 可動性情報の取得処理
/// </summary>
/// <returns>可動性情報</returns>
const bool GameObject::GetMobility() const
{
	return is_mobility;
}

int GameObject::SetOwnerScene(class SceneBase* scene)
{
	return 0;
}