#pragma once
#pragma once
#include "PlayerStateBase.h"
#include "../../../../Utility/Vector2D.h"

/// <summary>
/// ジャンプ状態
/// </summary>
class SquatState : public PlayerStateBase
{
private:
	//入力情報
	class InputManager* input;


public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="p">プレイヤー情報</param>
	SquatState(class Player* p);

	//デストラクタ
	virtual ~SquatState();

public:
	//初期化処理関数
	virtual void Initialize() override;

	//終了処理関数
	virtual void Finalize() override;

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() const override;

	//状態の取得
	virtual ePlayerState GetState() const override;
};

