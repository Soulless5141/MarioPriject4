#pragma once

#include "../Objects/GameObjectManager.h"
#include <vector>
#include <string>

/// <summary>
/// シーンタイプ
/// </summary>
enum class eSceneType
{
	title,
	in_game,
	re_start,
	result,
	exit,
};

/// <summary>
/// シーン基底クラス
/// </summary>
class SceneBase
{
public:
	GameObjectManager* gm = GameObjectManager::Get();
	Vector2D	screen_offset;	// スクリーンオフセット
	std::vector<GameObject*> game_objects_list;

public:
	SceneBase() :
		screen_offset(0.0f)
	{

	}
	virtual ~SceneBase()
	{
		// 解放忘れ防止
		Finalize();
	}

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize()
	{
		screen_offset.y = 16.0f;
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>次のシーンタイプ情報</returns>
	virtual eSceneType Update(const float& delta_second)
	{
		// 生成するオブジェクトがあれば、オブジェクトリスト内に挿入する
		
		gm->CheckCreateObject();

		gm->CheckDestroyObject();

		game_objects_list = gm->GetObjectsList();

		// リスト内のオブジェクトを更新する
		for (GameObject* obj : game_objects_list)
		{
			obj->Update(delta_second);
		}

		// 当たり判定確認処理
		for (int i = 0; i < game_objects_list.size(); i++)
		{
			if (eMobilityType::Stationary == game_objects_list[i]->GetMobility())
			{
				continue;
			}

			for (int j = 0; j < game_objects_list.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				CheckCollision(game_objects_list[i], game_objects_list[j]);
			}
		}

		// 現在のシーン情報を返却する
		return GetNowSceneType();
	}

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw()
	{
		game_objects_list = gm->GetObjectsList();
		// オブジェクトリスト内のオブジェクトを描画する
		for (GameObject* obj : game_objects_list)
		{
			obj->Draw(screen_offset);
		}
	}

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize()
	{

	}

	/// <summary>
	/// 現在のシーンタイプ取得処理
	/// </summary>
	/// <returns>現在のシーンタイプ情報</returns>
	virtual const eSceneType GetNowSceneType() const = 0;

	/// <summary>
	/// 当たり判定確認処理
	/// </summary>
	/// <param name="target">1つ目のゲームオブジェクト</param>
	/// <param name="partner">2つ目のゲームオブジェクト</param>
	virtual void CheckCollision(GameObject* target, GameObject* partner)
	{
	}

public:


	/// <summary>
	/// スクリーンオフセット情報取得処理
	/// </summary>
	/// <returns>スクリーンオフセット値</returns>
	const Vector2D GetScreenOffset() const
	{
		return screen_offset;
	}
};
