#pragma once

#include "../../../Objects/GameObject.h"
#include "../Enemy/EnemyBase.h"
#include "State/Enum/PlayerState.h"

#define FRICTION (3.612)		//摩擦力

// プレイヤー状態
enum ePlayerMode
{
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
	const int animation_num[4] = { 1,2,3,2 };
	float power_upanddown_time;						// パワーアップ時間

private:
	class PlayerStateBase* state = nullptr;
	float g_velocity = 0.0f;

public:
	Vector2D velocity = Vector2D(0.0f);
	Vector2D box_size = Vector2D(0.0f);
	float f_velocity = 0.0f;				//減速速度
	bool is_fly;							//空中にいるかどうか
	float damage_time;						//ダメージを受けた際無敵になっている時間
                                   

public:
	int sound;
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

	/// <summary>
	/// パワーアップ時のアニメーション制御
	/// </summary>
	/// <param name="delta_second"></param>
	void PowerUpAnim(float delta_second);

	/// <summary>
	/// powerダウン時のアニメーション制御
	/// </summary>
	/// <param name="delta_second"></param>
	void PowerDownAnim(float delta_second);

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

	void SetReverse(bool TF);

	float GetPowerUpTime();
};
