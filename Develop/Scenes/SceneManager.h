#pragma once


#include "../Utility/Singleton.h"
#include "SceneBase.h"

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneBase* current_scene;	// 現在のシーン情報

public:
	SceneManager();
	~SceneManager();

public:
	void Initialize();
	bool Update(float delta_second);
	void Finalize();


	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	/// <param name="next_type">次のシーンタイプ</param>
	void ChangeScene(eSceneType next_type);

private:
	/// <summary>
	/// シーン生成処理
	/// </summary>
	/// <param name="next_type">次のシーンタイプ</param>
	/// <returns>生成したシーン情報のポインタ</returns>
	SceneBase* CreateScene(eSceneType next_type);

	/// <summary>
/// 描画処理
/// </summary>
	void Graph() const;
};