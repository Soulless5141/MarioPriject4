#include "StoppedState.h"

#include "DxLib.h"
#include "../../../../Utility/InputManager.h"
#include "../Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="p">プレイヤー情報</param>
StoppedState::StoppedState(class Player* p)
	: PlayerStateBase(p)
	, input(nullptr)
{

}

/// <summary>
/// デストラクタ
/// </summary>
StoppedState::~StoppedState()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void StoppedState::Initialize()
{
	//Boxのサイズを設定する
	player->box_size = Vector2D(32.0f);

	//入力情報を取得
	input = InputManager::Get();
}

/// <summary>
/// 終了処理
/// </summary>
void StoppedState::Finalize()
{

}

/// <summary>
/// 更新処理
/// </summary>
void StoppedState::Update()
{
	//移動状態に遷移
	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	{
		//移動状態に遷移
		player->SetNextState(ePlayerState::eRun);
	}

	//ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		//停止状態に遷移
		player->SetNextState(ePlayerState::eJump);
	}

	//しゃがみ状態に遷移
	if (input->GetKey(KEY_INPUT_S))
	{
		//移動状態に遷移
		player->SetNextState(ePlayerState::eSquat);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void StoppedState::Draw() const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//描画
	/*DrawBox(x, y, x + (int)(player->box_size.x), y + (int)(player->box_size.y),
		GetColor(255, 0, 0), TRUE);*/
}

/// <summary>
/// 現在のステート情報を取得する
/// </summary>
/// <returns>現在のステート情報</returns>
ePlayerState StoppedState::GetState() const
{
	return ePlayerState::eIdle;
}