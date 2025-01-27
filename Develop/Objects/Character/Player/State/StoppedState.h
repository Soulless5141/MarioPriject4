#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// 停止状態
/// </summary>
class StoppedState : public PlayerStateBase
{
private:
	//入力情報
	class InputManager* input;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="p">プレイヤー情報</param>
	StoppedState(class Player* p);

	//デストラクタ
	virtual ~StoppedState();

public:
	//初期化処理関数
	virtual void Initialize() override;

	//終了処理関数
	virtual void Finalize() override;

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() const override;

	//現在のステート情報を取得する
	virtual ePlayerState GetState() const override;
};

