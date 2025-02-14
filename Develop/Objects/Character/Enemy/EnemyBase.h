#pragma once

#include "../../../Objects/GameObject.h"
#include "../../../Objects/GameObjectManager.h"

#define ENEMY_SPEED (15)

class EnemyBase : public GameObject
{
protected:
	std::vector<int> animation;
	float animation_time = 0;					// �A�j���[�V��������
	int animation_count = 0;					// �A�j���[�V�����Y��
	float g_velocity;
	Vector2D velocity = Vector2D(0.0f);

	bool die = false;

	GameObjectManager* gm = GameObjectManager::Get();

public:
	EnemyBase() = default;
	~EnemyBase()
	{

	}
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() override;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Update(float delta_second) override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void Movement(float delta_second);
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() override;
	/// <summary>
	/// �����蔻�菈��
	/// </summary>
	/// <param name="object">���������I�u�W�F�N�g</param>
	virtual void OnHitCollision(GameObject* object) override;
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void AnimationControl(float delta_second);
};

