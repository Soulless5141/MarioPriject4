#include "SceneManager.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "InGameScene.h"
#include "ResultScene.h"
#include "../Utility/Application.h"

SceneManager::SceneManager() :
	current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize()
{
	// 最初のシーンをタイトル画面にする
	ChangeScene(eSceneType::title);
}

bool SceneManager::Update(float delta_second)
{
	// シーンの更新
	eSceneType next_scene_type = current_scene->Update(GetDeltaSecond());

	// 描画処理
	Graph();

	// 現在のシーンタイプが次のシーンタイプと違っているか？
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// シーン切り替え処理
		ChangeScene(next_scene_type);
	}

	return 0;
}

void SceneManager::Finalize()
{
	// シーン情報が生成されていれば、削除する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

 /*<summary>
 シーン切り替え処理
 </summary>
 <param name="next_type">次のシーンタイプ</param>*/
void SceneManager::ChangeScene(eSceneType next_type)
{
	// 次のシーンを生成する
	SceneBase* next_scene = CreateScene(next_type);

	// エラーチェック
	if (next_scene == nullptr)
	{
		throw ("シーンが生成できませんでした\n");
	}

	// シーン情報が格納されていたら、削除する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// 次のシーンの初期化
	next_scene->Initialize();

	// 現在シーンの上書き
	current_scene = next_scene;
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="next_type">次のシーンタイプ</param>
/// <returns>生成したシーン情報のポインタ</returns>
SceneBase* SceneManager::CreateScene(eSceneType next_type)
{
	// シーンタイプによって、生成するシーンを切り替える
	switch (next_type)
	{
	case eSceneType::title:
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::in_game:
	case eSceneType::re_start:
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::result:
		return dynamic_cast<SceneBase*>(new ResultScene());
	default:
		return nullptr;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Graph() const
{
	// 画面の初期化
	ClearDrawScreen();

	// シーンの描画処理
	current_scene->Draw();

	// 裏画面の内容を表画面に反映する
	ScreenFlip();
}