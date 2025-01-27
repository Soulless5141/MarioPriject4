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
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
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
/// �������̎擾����
/// </summary>
/// <returns>�������</returns>
const bool GameObject::GetMobility() const
{
	return is_mobility;
}

int GameObject::SetOwnerScene(class SceneBase* scene)
{
	return 0;
}