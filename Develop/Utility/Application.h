#pragma once
#include "../Scenes/SceneManager.h"
#include "Singleton.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include <string>

/**********************************************************
* マクロ定義
***********************************************************/
#define	D_SUCCESS		(0)		// 成功
#define	D_FAILURE		(-1)	// 失敗

#define D_WIN_MAX_X		(640)	// スクリーンサイズ（幅）
#define D_WIN_MAX_Y		(480)	// スクリーンサイズ（高さ）
#define D_COLOR_BIT		(32)	// カラービット

/**********************************************************
* プロトタイプ宣言
***********************************************************/
/// <summary>
/// フレーム制御
/// </summary>
void FreamControl();

/// <summary>
/// 1フレーム当たりの時間を取得する
/// </summary>
/// <returns>1フレーム当たりの時間</returns>
const float& GetDeltaSecond();

/// <summary>
/// エラー内容を出力する
/// </summary>
/// <returns>終了状態の値</returns>
int ErrorThrow(std::string error_log);

class Application : public Singleton<Application>
{
public:
	InputManager* input = InputManager::Get();
	ResourceManager* rm = ResourceManager::Get();
	SceneManager* scene = SceneManager::Get();

public:	
	Application();
	~Application();

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	void WakeUp();

	/// <summary>
	///  実行処理
	/// </summary>
	void Run();

	/// <summary>
	/// 終了時処理
	/// </summary>
	void Shutdown();

private:
	void UpdateDeltaTime();
};

