#include "Player.h"

#include <cmath>

#include "../../../Utility/InputManager.h"
#include "State/Factory/PlayerStateFactory.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f)
#define D_GRAVITY (9.807f)     //重力加速度(m/ss)

Player::Player() :
	dekamarimation_animation(),
	dekamario_animation(),
	faiyamario_animation(),
	mario_animation(),
	starmario_animation(),
	starsmallmario_animation(),
	velocity(0.0f),
	player_state(ePlayerState::eIdle),
	animation_time(0.0f),
	animation_count(0),
	power_up_time(0),
	enemy(NULL),
	move_time(0)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	dekamarimation_animation = rm->GetImages("Resource/Images/Mario/dekamarimation.png", 3, 3, 1, 32, 32);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 32);
	faiyamario_animation = rm->GetImages("Resource/Images/Mario/faiyamario.png", 9, 9, 1, 32, 32);
	mario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	//starmario_animation = rm->GetImages("Resource/Images/Mario/starmario.png", 11, 11, 1, 32, 32);
	//starsmallmario_animation = rm->GetImages("Resource/Images/Mario/starsmallmario.png", 11, 11, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);

	// 初期のアニメーション
	image = mario_animation[0];

	// レイヤーの設定
	z_layer = 5;

	//初期ステータス設定
	player_state = ePlayerState::eIdle;
	g_velocity = 0;
	velocity = Vector2D(0.0);

	// 可動性の設定
	is_mobility = eMobilityType::Movable;
}

void Player::Update(float delta_second)
{
	//移動処理
	Movement(delta_second);

	//状態別の描画処理を行う
	AnimationControl(delta_second);
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

// 終了処理
void Player::Finalize()
{
	PlayerStateFactory::Finalize();

	// 動的配列の解放
	dekamarimation_animation.clear();
	mario_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Player::OnHitCollision(GameObject* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
		
	}
}

/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
ePlayerMode Player::GetPlayerMode() const
{
	return player_mode;
}

ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

void Player::SetDefoltX()
{
	animation_count = 0;
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Movement(float delta_second)
{
	// stateの変更処理
	state = PlayerStateFactory::Get((*this), player_state);

	//重力速度の計算
	g_velocity = D_GRAVITY / 444.0f;

	/*move_time += delta_second;
	if (move_time >= (1.0f / 30.0f))
	{*/
	velocity.y += g_velocity;

	//状態別の更新処理を行う
	state->Update();

	//移動の実行
	location += velocity * D_PLAYER_SPEED * delta_second;

	//384.0f地点を地面と仮定
	if (384.0f <= location.y)
	{
		location.y = 384.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}
	if (0.0 >= location.x)
	{
		location.x = 0.0f;
	}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::AnimationControl(float delta_second)
{
	switch (player_state)
	{
	case ePlayerState::eIdle:
		switch (player_mode)
		{
		case DEKAMARIMATION:
			break;
		case DEKAMARIO:
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}
		image = mario_animation[0];
		break;
	case ePlayerState::eRun:

		// 移動中のアニメーション
		animation_time += delta_second;
		if (animation_time >= (1.0f / 16.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 4)
			{
				animation_count = 0;
			}
			// 画像の設定
			image = mario_animation[animation_num[animation_count]];

		}
		
		// 画像反転処理
		if (velocity.x < 0 && velocity.y == 0)
		{
			reverse = true;
		}
		else if (velocity.x > 0 && velocity.y == 0)
		{
			reverse = false;
		}

		break;
	case ePlayerState::eJump:
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		break;
	case ePlayerState::sSquat:
		break;
	case ePlayerState::eDamage:
		break;
	case ePlayerState::eGoal:
		break;
	default:
		break;
	}

	if (velocity.y != 0)
	{
		image = mario_animation[5];
	}
}


/// <summary>
/// 次のstateを設定
/// </summary>
/// <param name="next_state">次のState</param>
void Player::SetNextState(ePlayerState next_state)
{
	this->player_state = next_state;
}

/// <summary>
/// 座標の取得
/// </summary>
Vector2D& Player::GetLocation()
{
	return this->location;
}

