#pragma once


#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"
#include "../Utility/ResourceManager.h"
#include "GameObject.h"

#include <string>


#define D_OBJECT_SIZE	(32.0f)			// 壁のサイズ

// ゲームオブジェクト基底クラス
class GameObjectManager : public GameObject
{
private:
	std::vector<GameObject*> create_objects;
	std::vector<GameObject*> destroy_objects;
	std::vector<GameObject*> game_objects_list;

	static GameObjectManager* instance;

public:
	GameObjectManager();
	virtual ~GameObjectManager();

public:
	void CheckCreateObject();
	void CheckDestroyObject();
	void CheckCollision(GameObject* target, GameObject* partner);
	void Draw(const Vector2D& screen_offset) const;
	virtual void Update(float screen_offset);
	std::vector<GameObject*>GetObjectsList() const;
	static GameObjectManager* GetInstance();

	template<class T>
	T* CreateGameObject(const Vector2D& generate_location)
	{
		// 生成するゲームオブジェクトクラスを動的確保
		T* new_instance = new T();
		// GameObjectBaseを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);
		// エラーチェック
		if (new_object == nullptr)
		{
			// 動的確保したメモリの開放
			delete new_instance;
			// 例外テキストを通知
			throw std::string("ゲームオブジェクトが生成できませんでした");
			return nullptr;
		}
		// シーン情報の設定
		//new_object->SetOwnerScene(this);
		// オブジェクトの初期化
		new_object->Initialize();
		// 位置情報の設定
		new_object->SetLocation(generate_location);
		// 生成オブジェクトリストの末尾に格納する
		create_objects.push_back(new_object);
		// 生成したゲームオブジェクトのポインタを返す
		return new_instance;
	}

	/// <summary>
	/// オブジェクト破棄処理
	/// </summary>
	/// <param name="target">破棄を行うゲームオブジェクトのポインタ</param>
	void DestroyGameObject(GameObjectManager* target)
	{
		// ヌルポチェック
		if (target == nullptr)
		{
			return;
		}

		// 破棄オブジェクトリスト内にあれば、追加しない
		for (GameObject* obj : destroy_objects)
		{
			if (obj == target)
			{
				return;
			}
		}

		// 破棄を行うオブジェクトリストに追加する
		destroy_objects.push_back(target);
	}
};

