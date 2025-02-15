#include "JumpingState.h"

#include "DxLib.h"
#include "../Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="p">プレイヤー情報</param>
JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p)
{

}

/// <summary>
/// デストラクタ
/// </summary>
JumpingState::~JumpingState()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void JumpingState::Initialize()
{
	if (this->player->velocity.y == 0)
	{
		this->player->velocity.y -= 5.0f; //ジャンプ力
	}
	
	ResourceManager* rm = ResourceManager::Get();
	this->player->sound = rm->GetSounds("Resource/Sounds/SE_SuperJump.wav");
	this->player->is_fly = TRUE;
	input = InputManager::Get();
	PlaySoundMem(player->sound, DX_PLAYTYPE_BACK);
}

/// <summary>
/// 終了処理
/// </summary>
void JumpingState::Finalize()
{

}

/// <summary>
/// 更新処理
/// </summary>
void JumpingState::Update()
{


	//地面に触れたら
	if (player->is_fly == false)
	{
		//停止状態に遷移
		player->SetNextState(ePlayerState::eIdle);
	}
	if (input->GetKey(KEY_INPUT_SPACE))
	{
		player->velocity.y -= (D_GRAVITY / 444.0f) / 1.2;
	}
	else
	{
		//停止状態に遷移
		player->SetNextState(ePlayerState::eIdle);
	
	}
	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	{
		//移動状態に遷移
		player->SetNextState(ePlayerState::eRun);
	}

}

/// <summary>
/// 描画処理
/// </summary>
void JumpingState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	/*DrawBox(x, y, x + (int)(player->box_size.x), y + (int)(player->box_size.y),
		GetColor(0, 0, 255), FALSE);*/
}

/// <summary>
/// 現在のステート情報を取得する
/// </summary>
/// <returns>現在のステート情報</returns>
ePlayerState JumpingState::GetState() const
{
	return ePlayerState::eJump;
}

