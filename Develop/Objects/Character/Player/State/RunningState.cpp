#include "RunningState.h"

#include "DxLib.h"
#include "../Player.h"

#define MAX_SPEED (4.0f)

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="p">プレイヤー情報</param>
RunningState::RunningState(class Player* p)
	: PlayerStateBase(p)
{

}

/// <summary>
/// デストラクタ
/// </summary>
RunningState::~RunningState()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void RunningState::Initialize()
{
	if (this->player->velocity.x == 0)
	{
		this->player->SetDefoltX();
	}
	accel_force = 0.0f;
	//入力情報を取得
	input = InputManager::Get();
}

/// <summary>
/// 終了処理
/// </summary>
void RunningState::Finalize()
{

}

/// <summary>
/// 更新処理
/// </summary>
void RunningState::Update()
{
	accel_force = FRICTION / 444.0f;
	if (input->GetKey(KEY_INPUT_A))
	{
		player->SetReverse(true);
		if (input->GetKey(KEY_INPUT_LSHIFT))
		{
			if (player->velocity.x > (-MAX_SPEED * 1.75f))
			{
				player->velocity.x -= accel_force;
			}
		}
		else
		{
			if (player->velocity.x > -MAX_SPEED)
			{
				player->velocity.x -= accel_force;
			}
			else
			{
				player->velocity.x += accel_force;
			}
		}
		player->f_velocity = 0.0f;
	}
	else if (input->GetKey(KEY_INPUT_D))
	{
		player->SetReverse(false);
		if (input->GetKey(KEY_INPUT_LSHIFT))
		{
			if (player->velocity.x < (MAX_SPEED * 1.75f))
			{
				player->velocity.x += accel_force;
			}
		}
		else
		{
			if (player->velocity.x < MAX_SPEED)
			{
				player->velocity.x += accel_force;
			}
			else
			{
				player->velocity.x -= accel_force;
			}
		}

		player->f_velocity = 0.0f;
	}
	else
	{
		//停止状態に遷移
		player->SetNextState(ePlayerState::eIdle);
		accel_force = 0.0f;
	}
	if (input->GetKey(KEY_INPUT_SPACE))
	{
		player->velocity.y -= (D_GRAVITY / 444.0f) / 1.2;
	}
	if (input->GetKeyDown(KEY_INPUT_SPACE) && player->velocity.x != 0)
	{
		//移動状態に遷移
		player->SetNextState(ePlayerState::eJump);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void RunningState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	DrawBox(x, y, x + (int)(player->box_size.x), y + (int)(player->box_size.y),
		GetColor(255, 0, 0), TRUE);
}

/// <summary>
/// 現在のステート情報を取得する
/// </summary>
/// <returns>現在のステート情報</returns>
ePlayerState RunningState::GetState() const
{
	return ePlayerState::eRun;
}