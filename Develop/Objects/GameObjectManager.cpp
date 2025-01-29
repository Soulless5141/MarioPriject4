#include "GameObjectManager.h"
#include "../Scenes/SceneBase.h"
#include <vector>
#include "DxLib.h"

// 静的メンバ変数定義
GameObjectManager* GameObjectManager::instance = nullptr;	// 自クラスのポインタ

GameObjectManager::GameObjectManager() :
	create_objects(),
	destroy_objects(),
	game_objects_list()
{

}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::CheckCreateObject()
{
	// 生成するオブジェクトがあれば、オブジェクトリスト内に挿入する
	if (!create_objects.empty())
	{
		for (GameObject* obj : create_objects)
		{
			// レイヤー情報を基に順番を入れ替える
			int z_layer = obj->GetZLayer();
			std::vector<GameObject*>::iterator itr = game_objects_list.begin();	// オブジェクトリストの先頭
			// リストの末尾になるまで走査する
			for (; itr != game_objects_list.end(); itr++)
			{
				// Zレイヤーが大きい場所に要素を追加する
				// 例 itr->ZLayer{1, 1, 2, 3}、z_layer = 2 の時
				//    itr->ZLayer{1, 1, 2, z_layer, 3}とする
				if (z_layer < (*itr)->GetZLayer())
				{
					break;
				}
			}
			// リストの途中に挿入する
			game_objects_list.insert(itr, obj);
		}
		// 生成リストを解放する
		create_objects.clear();
	}
}

void GameObjectManager::CheckDestroyObject()
{
	if (!destroy_objects.empty())
	{
		for (GameObject* obj : destroy_objects)
		{
			std::vector<GameObject*>::iterator itr = game_objects_list.begin();	// オブジェクトリストの先頭
			// リストの末尾になるまで走査する
			for (; itr != game_objects_list.end(); itr++)
			{
				// リスト内にあれば、削除する
				if ((*itr) == obj)
				{
					game_objects_list.erase(itr);
					obj->Finalize();
					delete obj;
					break;
				}
			}
		}
		// 動的配列の開放
		destroy_objects.clear();
	}
}

void GameObjectManager::CheckCollision(GameObject* target, GameObject* partner)
{
	// ヌルポチェック
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// 当たり判定情報を取得
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	// 当たり判定が有効か確認する
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// 線分の始点と終点を設定する
		tc.point[0] += target->GetLocation() - 32;
		tc.point[1] += target->GetLocation() + 32;
		pc.point[0] += partner->GetLocation() - 32;
		pc.point[1] += partner->GetLocation() + 32;

		// カプセル同士の当たり判定
		if (IsCheckCollision(tc, pc))
		{
			// 当たっていることを通知する
			partner->OnHitCollision(target);
			target->OnHitCollision(partner);

		}
	}
}

std::vector<GameObject*>GameObjectManager::GetObjectsList() const
{
	return game_objects_list;
}

GameObjectManager* GameObjectManager::GetInstance()
{
	// インスタンスが生成されていない場合、生成する
	if (instance == nullptr)
	{
		instance = new GameObjectManager();
	}

	return instance;
}