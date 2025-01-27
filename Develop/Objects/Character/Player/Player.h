#pragma once

#include "../../../Objects/GameObject.h"
#include "../../../Utility/ResourceManager.h"
#include "../Enemy/EnemyBase.h"
#include "State/Enum/PlayerState.h"

// プレイヤー状態
enum ePlayerMode
{
	DEKAMARIMATION,	// パワーアップしている状態状態
	DEKAMARIO,		// でか状態
	FAIYAMARIO,		// ファイア状態
	MARIO,			// ちびマリオ状態
	STARMARIO,		// でかStar状態
	STARSMALLMARIO,	// ちびStar状態
};

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

private:
	std::vector<int> dekamarimation_animation;		// 移動のアニメーション画像
	std::vector<int> dekamario_animation;		// 死亡のアニメーション画像
	std::vector<int> faiyamario_animation;		// ジャンプのアニメーション画像
	std::vector<int> mario_animation;		// しゃがんだ時のアニメーション画像
	std::vector<int> starmario_animation;		// ゴールした時のアニメーション画像

	std::vector<int> starsmallmario_animation;

	ePlayerMode player_mode;				// プレイヤー状態
	ePlayerState player_state;
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	float move_time;
	bool scroll_end;
	const int animation_num[4] = { 1,2,3,2 };
	int power_up_time;						// パワーアップ時間

private:
	class PlayerStateBase* state = nullptr;
	float g_velocity = 0.0f;

public:
	Vector2D velocity = Vector2D(0.0f);
	Vector2D box_size = Vector2D(0.0f);

public:
	int sound;
	float scroll;
	class EnemyBase* enemy;					// エネミーの状態確認

public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

public:

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	ePlayerMode GetPlayerMode() const;

	/// <summary>
	/// プレイヤーの現在形態を取得する
	/// </summary>
	/// <returns>プレイヤーの現在形態</returns>
	ePlayerState GetPlayerState() const;

	void SetDefoltX();

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);

public:
	/// <summary>
	///次のStateを設定 
	/// </summary>
	/// <param name="next_state">次のState</param>
	void SetNextState(ePlayerState next_state);

	/// <summary>
	///座標の取得
	/// </summary>
	Vector2D& GetLocation();
};


