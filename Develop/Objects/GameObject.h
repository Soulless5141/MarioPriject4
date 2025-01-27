#pragma once
#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"
#include "../Utility/Camera.h"

/// <summary>
/// �����̎��
/// </summary>
enum eMobilityType
{
	Stationary,		// �Œ�
	Movable,		// ��
};

class GameObject/* : public GameObjectManager*/
{
protected:
	class SceneBase* owner_scene;	// ���L����V�[�����
	Vector2D location;
	Collision collision;
	int image;
	unsigned char z_layer;
	bool is_mobility;
	bool reverse;
	

public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void Initialize();
	virtual void Finalize();
	virtual void Draw(const Vector2D&) const;
	virtual void Update(float);
	virtual void OnHitCollision(GameObject*);
	const Vector2D& GetLocation() const;
	void SetLocation(const Vector2D&);
	const Collision& GetCollision() const;
	const unsigned char GetZLayer() const;
	const bool GetMobility() const;
	/// <summary>
	/// ���L�V�[�����̐ݒ�
	/// </summary>
	/// <param name="scene">���L�V�[�����</param>
	int SetOwnerScene(class SceneBase* scene);
};

