#pragma once
#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"
#include "../Utility/Camera.h"

/// <summary>
/// 可動性の種類
/// </summary>
enum eMobilityType
{
	Stationary,		// 固定
	Movable,		// 可動
};

class GameObject/* : public GameObjectManager*/
{
protected:
	class SceneBase* owner_scene;	// 所有するシーン情報
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
	/// 所有シーン情報の設定
	/// </summary>
	/// <param name="scene">所有シーン情報</param>
	int SetOwnerScene(class SceneBase* scene);
};

