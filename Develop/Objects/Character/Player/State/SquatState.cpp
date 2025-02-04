#include "SquatState.h"

#include "DxLib.h"
#include "../../../../Utility/InputManager.h"
#include "../Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="p">プレイヤー情報</param>
SquatState::SquatState(class Player* p)
	: PlayerStateBase(p)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SquatState::~SquatState()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void SquatState::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
}

/// <summary>
/// 終了処理
/// </summary>
void SquatState::Finalize()
{

}

/// <summary>
/// 更新処理
/// </summary>
void SquatState::Update()
{
	//左右入力があるなら
	InputManager* input = InputManager::Get();

	//地面に触れたら
	if (player->velocity.y >= 0)
	{
		//左右入力があるなら
		InputManager* input = InputManager::Get();

		if (input->GetKey(KEY_INPUT_S))
		{
			
		}

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
void SquatState::Draw() const
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
ePlayerState SquatState::GetState() const
{
	return ePlayerState::eSquat;
}

