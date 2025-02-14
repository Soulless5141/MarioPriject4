#include "Player.h"

#include <cmath>

#include "../../../Utility/InputManager.h"
#include "State/Factory/PlayerStateFactory.h"
#include "../../../Utility/Camera.h"
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
	move_time(0),
	damage_time(0.0f),
	is_fly(false),
	player_mode(ePlayerMode::MARIO),
	sound()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	dekamarimation_animation = rm->GetImages("Resource/Images/Mario/dekamarimation.png", 3, 3, 1, 32, 64);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	faiyamario_animation = rm->GetImages("Resource/Images/Mario/faiyamario.png", 9, 9, 1, 32, 32);
	mario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	//starmario_animation = rm->GetImages("Resource/Images/Mario/starmario.png", 11, 11, 1, 32, 32);
	//starsmallmario_animation = rm->GetImages("Resource/Images/Mario/starsmallmario.png", 11, 11, 1, 32, 32);
	player_mode = ePlayerMode::MARIO;
	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.box_size = 32.0f;
	collision.pivot = location;
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
	is_fly = FALSE;
	reverse = FALSE;
	// 可動性の設定
	
}

void Player::Update(float delta_second)
{
	if (power_up_time <= 0.0f && power_down_time <= 0.0f)
	{
		//移動処理
		Movement(delta_second);

		//状態別の描画処理を行う
		AnimationControl(delta_second);

		damage_time -= delta_second;
		if (damage_time <= 0.0f)
		{
			damage_time = 0.0f;
		}

		power_up_time = 0.0f;
	}
	else
	{
		if (power_up_time > 0.0f)
		{
			PowerUpAnim(delta_second);
		}
		else if (power_down_time > 0.0f)
		{
			//状態別の描画処理を行う
			AnimationControl(delta_second);
		}
	}

}

void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
	DrawFormatString(100, 100, 0x000000, "%f", damage_time);
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
	Collision oc = hit_object->GetCollision();
	Vector2D diff;
	Vector2D dis;

	// 当たった、オブジェクトが壁だったら
	if (oc.object_type == eObjectType::eBlock)
	{
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//プレイヤーの右下とオブジェクトの左上の判定
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);
				
				//押し戻し
				if (diff.x <= diff.y && diff.x != 0.0f)
				{
					location.x -= diff.x;
					velocity.x = 0.0f;
				}
				else if(diff.x != 0.0f)
				{
					location.y -= diff.y;
					is_fly = false;
					velocity.y = 0;
				}
			}
			else
			{
				//プレイヤーの右上とオブジェクトの左下の判定
				diff = Vector2D((this->location.x + collision.box_size.x / 2), (this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - oc.box_size.x / 2), (hit_object->GetLocation().y + oc.box_size.y / 2));

				//押し戻し
				if (diff.x > diff.y && dis.y <= box_size.y / 2)
				{
					location.x -= diff.x;
					velocity.x = 0.0f;
				}
				else if(diff.x != 0.0f)
				{
					location.y -=  diff.y;
					velocity = 0.0f;
				}

			}
		}
		else
		{
			if (dis.y >= 0)
			{
				//プレイヤーの左上とオブジェクトの右下の判定
				diff = (this->location - collision.box_size / 2) - (hit_object->GetLocation() + oc.box_size / 2);

				//押し戻し
				if (-diff.x < -diff.y || dis.y == 0)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity = 0.0f;
				}
			}
			else
			{
				//プレイヤーの左下とオブジェクトの右上の判定
				diff = Vector2D((this->location.x - collision.box_size.x / 2), (this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + oc.box_size.x / 2), (hit_object->GetLocation().y - oc.box_size.y / 2));

				//押し戻し
				if (-diff.x < diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					is_fly = false;
					velocity.y = 0;
				}
			}
		}
	}

	// 当たった、オブジェクトが敵だったら
	if (oc.object_type == eObjectType::eEnemy)
	{
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//プレイヤーの右下とオブジェクトの左上の判定
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);

				//押し戻し
				if (diff.x <= diff.y)
				{
					if (damage_time <= 0.0f)
					{
						if (player_mode == ePlayerMode::DEKAMARIO)
						{
							collision.box_size.y = 32.0f;
						}
						power_down_time = 0.5f;
						player_state = ePlayerState::eDamage;
						damage_time = 1.0f;
					}					
				}
				else
				{
					g_velocity = 0.0f;
					velocity.y = -3.0f;
				}
			}
			else
			{
				if (damage_time <= 0.0f)
				{
					if (player_mode == ePlayerMode::DEKAMARIO)
					{
						collision.box_size.y = 32.0f;
					}
					power_down_time = 0.5f;
					player_state = ePlayerState::eDamage;
					damage_time = 1.0f;
				}
			}
		}
		else
		{
			if (dis.y >= 0)
			{
				if (damage_time <= 0.0f)
				{
					if (player_mode == ePlayerMode::DEKAMARIO)
					{
						collision.box_size.y = 32.0f;
					}
					power_down_time = 0.5f;
					player_state = ePlayerState::eDamage;
					damage_time = 1.0f;
				}
			}
			else
			{
				//プレイヤーの左下とオブジェクトの右上の判定
				diff = Vector2D((this->location.x - collision.box_size.x / 2), (this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + oc.box_size.x / 2), (hit_object->GetLocation().y - oc.box_size.y / 2));

				//押し戻し
				if (-diff.x < diff.y)
				{
					if (damage_time <= 0.0f)
					{
						if (player_mode == ePlayerMode::DEKAMARIO)
						{
							collision.box_size.y = 32.0f;
						}
						power_down_time = 0.5f;
						player_state = ePlayerState::eDamage;
						damage_time = 1.0f;
					}
				}
				else
				{
					g_velocity = 0.0f;
					velocity.y = -3.0f;
				}
			}
		}
	}

	if (oc.object_type == eObjectType::eItem)
	{
		if (player_mode == ePlayerMode::MARIO)
		{
			location.y -= 16.0f;
			collision.box_size.y = 64.0f;
			player_mode = ePlayerMode::DEKAMARIO;

			power_up_time = 0.5f;
		}
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
	Camera* camera = Camera::Get();
	// stateの変更処理
	state = PlayerStateFactory::Get((*this), player_state);

	//重力速度の計算
	g_velocity = D_GRAVITY / 444.0f;
	f_velocity = FRICTION / 444.0f;

	/*move_time += delta_second;
	if (move_time >= (1.0f / 30.0f))
	{*/
	velocity.y += g_velocity;

		

	//状態別の更新処理を行う
	state->Update();

	//移動の実行
	location += velocity * D_PLAYER_SPEED * delta_second;

	//384.0f地点を地面と仮定
	if (is_fly != true)
	{
		g_velocity = 0.0f;
	}
	if (location.x < camera->GetCameraLocation().x - (D_WIN_MAX_X / 2.1))
	{
		location.x = camera->GetCameraLocation().x - (D_WIN_MAX_X / 2.1);
		velocity.x = 0;
	}
	//if (location.y >= 384.0f)
	//{
	//	location.y = 384.0f;
	//	g_velocity = 0.0f;
	//	velocity.y = 0.0f;
	//}
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
		case DEKAMARIO:
			image = dekamario_animation[0];
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			image = mario_animation[0];
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}

		break;
	case ePlayerState::eRun:
		switch (player_mode)
		{
		case DEKAMARIO:
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
				image = dekamario_animation[animation_num[animation_count] + 1];

			}
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
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
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
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
		break;
	case ePlayerState::eSquat:
		switch (player_mode)
		{
		case DEKAMARIO:
			image = dekamario_animation[1];
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
		break;
	case ePlayerState::eDamage:
		switch (player_mode)
		{
		case DEKAMARIO:
			PowerDownAnim(delta_second);
			if (power_down_time <= 0.0f)
			{
				player_mode = ePlayerMode::MARIO;
			}
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			power_down_time -= delta_second;
			image = mario_animation[6];
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}
	
		break;
	case ePlayerState::eGoal:
		break;
	default:
		break;
	}

	if (is_fly == true)
	{
		switch (player_mode)
		{
		case DEKAMARIO:
			image = dekamario_animation[6];
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			image = mario_animation[5];
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}

	}

}

void Player::PowerUpAnim(float delta_second)
{
	power_up_time -= delta_second;
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = dekamarimation_animation[animation_count];
	}
}

void Player::PowerDownAnim(float delta_second)
{
	power_down_time -= delta_second;
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count--;
		if (animation_count <= 0)
		{
			animation_count = 2;
		}
		// 画像の設定
		image = dekamarimation_animation[animation_count];
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

void Player::SetReverse(bool TF)
{
	reverse = TF;
}

float Player::GetPowerUpTime()
{
	return this->power_up_time;
}

float Player::GetPowerDownTime()
{
	return this->power_down_time;
}