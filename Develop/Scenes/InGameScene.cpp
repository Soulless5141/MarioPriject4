#include "InGameScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "../Objects/GameObjectManager.h"
#include "../Objects/Character/Enemy/kuribo.h"
#include "../Objects/Character/Enemy/Nokonoko.h"
#include "../Objects/Block/Block.h"
#include "../Objects/Block/Dokan_Left_Down.h"
#include "../Objects/Block/Dokan_Right_Down.h"
#include "../Objects/Block/Dokan_Left_Up.h"]
#include "../Objects/Block/Dokan_Right_Up.h"
#include "../Objects/Block/Goal.h"
#include "../Objects/Block/Ground.h"
#include "../Objects/Block/Hatena.h"
#include "../Objects/Block/Stairs.h"
#include "../Objects/Item/Kinoko.h"
#include "DxLib.h"
#include <fstream>

InGameScene::InGameScene()
	: player(nullptr)
	, back_ground_stage(NULL)
	, ground_stage(NULL)
	, back_bgm(NULL)
	, pause_flag(false)
	, player_powerup_flag(false)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	// スクリーンオフセットを設定
	camera = Camera::Get();

	//配列初期化
	std::vector<int>initi_back(BLOCK_MAX_Y, back_ground_stage);
	haikei_block = std::vector<std::vector<int>>(BLOCK_MAX_X, initi_back);
	std::vector<int>initi_ground(BLOCK_MAX_Y, ground_stage);
	block = std::vector<std::vector<int>>(BLOCK_MAX_X, initi_ground);
	std::vector<GameObject*>initi_object(BLOCK_MAX_Y, nullptr);
	object = std::vector<std::vector<GameObject*>>(BLOCK_MAX_X, initi_object);

	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	GameObjectManager* gm = GameObjectManager::Get();

	ui_time = rm->GetImages("Resource/Images/UI/time.png")[0];

	ui_world = rm->GetImages("Resource/Images/UI/world.png")[0];

	ui_coin_1_score = rm->GetImages("Resource/Images/UI/uicoin_1.png")[0];

	ui_mario_score = rm->GetImages("Resource/Images/UI/name_mario.png")[0];

	player = gm->CreateGameObject<Player>(Vector2D(100, 384));

	gm->CreateGameObject<Kinoko>(Vector2D(200, 250));

	// マップデータ読み込み生成処理
	LoadBackStageMapCSV();
	LoadStageMapCSV();

	// BGMの読み込み
	back_bgm = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	//PlaySoundMem(back_bgm, DX_PLAYTYPE_BACK);
	__super::Initialize();
}

eSceneType InGameScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::Get();
	camera->CameraUpdate(player->GetLocation());		//プレイヤーの座標を基にカメラを更新

	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}

	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}

	if (player->GetPowerUpTime() > 0)
	{
		player_powerup_flag = !player_powerup_flag;
	}
	else
	{
		player_powerup_flag = false;
	}

	if (!pause_flag || !player_powerup_flag)
	{
		CreateStage();
		// 親クラスの更新処理を呼び出す
		__super::Update(delta_second);

		DeleteStage();
	}

	// シーン情報を返却する
	return GetNowSceneType();
}

void InGameScene::Draw()
{
	// 背景画像の描画
	Vector2D generate_location;
	for (int i = 0; i < haikei_block.size(); i++)
	{
		for (int j = 0; j < haikei_block[i].size(); j++)
		{
			generate_location = camera->ConvertLcoationToScreen(Vector2D(i * OBJECT_SIZE, j * OBJECT_SIZE) + screen_offset);
			DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, haikei_block[i][j], TRUE);
		}
	}

	DrawExtendGraph(510, 20, 580, 42, ui_time, TRUE);

	DrawExtendGraph(380, 20, 470, 42, ui_world, TRUE);

	DrawExtendGraph(220, 43, 310, 63, ui_coin_1_score, TRUE);

	DrawExtendGraph(90, 20, 180, 42, ui_mario_score, TRUE);


	// デバッグ用枠線だったもの
	/*DrawBoxAA(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, 0xff0000, false);
	DrawFormatString(10,0, 0x000000, "%f", camera->GetCameraLocation().x);*/

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	// UI系の描画処理
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="target">1つ目のゲームオブジェクト</param>
/// <param name="partner">2つ目のゲームオブジェクト</param>
void InGameScene::CheckCollision(GameObject* target, GameObject* partner)
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
		// カプセル同士の当たり判定
		tc.pivot = target->GetLocation();
		pc.pivot = partner->GetLocation();
		Vector2D distance = target->GetLocation() - partner->GetLocation();
		Vector2D col_size = (tc.box_size + pc.box_size) / 2;
		if (fabsf(distance.x) <= col_size.x && fabsf(distance.y) <= col_size.y)
		{
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
		//if (IsCheckCollision(tc, pc))
		//{
		//	// 当たっていることを通知する
		//	partner->OnHitCollision(target);
		//	target->OnHitCollision(partner);

		//}
	}
}

/// <summary>
/// ステージマップ（ブロック）読み込み処理
/// </summary>
void InGameScene::LoadStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Book.csv";

	ResourceManager* rm = ResourceManager::Get();

	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;

	// ファイル内の文字を確認していく
	while (true)
	{
		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 文字を抽出して格納
		else if (c != ' ' && c != '\n' && c != ',')
		{

			switch (c)
			{
				// 床
			case 'f':
				ground_stage = 'f';
				break;
				// 階段ブロック
			case 'B':
				ground_stage = 'B';
				break;
				// ブロック
			case 'b':
				ground_stage = 'b';
				break;
				// ？ブロック
			case 'h':
				ground_stage = 'h';
				break;
				//土管
			case 'd':
				ground_stage = 'd';
				break;
			case 'o':
				ground_stage = 'o';
				break;
			case 'A':
				ground_stage = 'A';
				break;
			case 'K':
				ground_stage = 'K';
				break;
				// クリボー
			case 'k':
				ground_stage = 'k';
				break;
				// ゴール
			case 'P':
				ground_stage = 'P';
				break;
			case 'G':
				ground_stage = 'G';
				break;
			case 'p':
				ground_stage = 'p';
				break;
				//ノコノコ
			case 'n':
				ground_stage = 'n';
				break;
			default:
				break;
			}
			// 格納
			block[x][y] = ground_stage;
			x++;
		}

		// 抽出した文字が空白文字なら、生成しないで次の文字を見に行く
		else if (c == ' ')
		{
			ground_stage = NULL;
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}
	// 開いたファイルを閉じる
	fclose(fp);
}

/*<summary>
ステージマップ読み込み処理
</summary>*/
void InGameScene::LoadBackStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Haikei.csv";

	ResourceManager* rm = ResourceManager::Get();

	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;

	// ファイル内の文字を確認していく
	while (true)
	{
		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 文字を抽出して格納
		else if (c != ' ' && c != '\n' && c != ',')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);

			switch (c)
			{
				//空の読み込み
			case 's':
				back_ground_stage = rm->GetImages("Resource/Images/sora.png", 1, 1, 1, 32, 32)[0];
				break;
				// 雲の読み込み
			case 'C':
				back_ground_stage = rm->GetImages("Resource/Images/cloud1.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'L':
				back_ground_stage = rm->GetImages("Resource/Images/cloud2.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'O':
				back_ground_stage = rm->GetImages("Resource/Images/cloud3.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'U':
				back_ground_stage = rm->GetImages("Resource/Images/cloud4.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'D':
				back_ground_stage = rm->GetImages("Resource/Images/cloud5.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'S':
				back_ground_stage = rm->GetImages("Resource/Images/cloud6.png", 1, 1, 1, 32, 32)[0];
				break;

				// 山の読み込み
			case 'm':
				back_ground_stage = rm->GetImages("Resource/Images/mountain_surface.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'o':
				back_ground_stage = rm->GetImages("Resource/Images/mountain_surface2.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'u':
				back_ground_stage = rm->GetImages("Resource/Images/mountain_surface1.png", 1, 1, 1, 32, 32)[0];
				break;
			case 't':
				back_ground_stage = rm->GetImages("Resource/Images/mountain_right.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'n':
				back_ground_stage = rm->GetImages("Resource/Images/mountain_left.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'a':
				back_ground_stage = rm->GetImages("Resource/Images/mountain_up.png", 1, 1, 1, 32, 32)[0];
				break;
				// 草の読み込み
			case 'G':
				back_ground_stage = rm->GetImages("Resource/Images/ha0.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'R':
				back_ground_stage = rm->GetImages("Resource/Images/ha1.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'A':
				back_ground_stage = rm->GetImages("Resource/Images/ha2.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'Q':
				back_ground_stage = rm->GetImages("Resource/Images/siro1.png", 1, 1, 1, 150, 150)[0];
			default:
				break;
			}

			// 配列に格納
			haikei_block[x][y] = back_ground_stage;
			x++;
		}

		// 抽出した文字が空白文字なら、生成しないで次の文字を見に行く
		else if (c == ' ')
		{
			back_ground_stage = NULL;
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}
	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::CreateStage()
{
	GameObjectManager* gm = GameObjectManager::Get();
	for (int x = 0; x < block.size(); x++)
	{
		for (int y = 0; y < block[x].size(); y++)
		{
			if (block[x][y] != NULL && ((float)x * OBJECT_SIZE) < (camera->GetCameraLocation().x + (D_WIN_MAX_X / 1.9)))
			{
				Vector2D genelate_location = Vector2D((float)x * OBJECT_SIZE, (float)y * OBJECT_SIZE);
				switch (block[x][y])
				{
					// 床
				case 'f':
					object[x][y] = gm->CreateGameObject<Ground>(genelate_location);
					break;
					// 階段ブロック
				case 'B':
					object[x][y] = gm->CreateGameObject<Stairs>(genelate_location);
					break;
					// ブロック
				case 'b':
					object[x][y] = gm->CreateGameObject<Block>(genelate_location);
					break;
					// ？ブロック
				case 'h':
					object[x][y] = gm->CreateGameObject<Hatena>(genelate_location);
					break;
					//土管
				case 'd':
					object[x][y] = gm->CreateGameObject<Dokan_Left_Up>(genelate_location);
					break;
				case 'o':
					object[x][y] = gm->CreateGameObject<Dokan_Right_Up>(genelate_location);
					break;
				case 'A':
					object[x][y] = gm->CreateGameObject<Dokan_Left_Down>(genelate_location);
					break;
				case 'K':
					object[x][y] = gm->CreateGameObject<Dokan_Right_Down>(genelate_location);
					break;
					// クリボー
				case 'k':
					object[x][y] = gm->CreateGameObject<kuribo>(genelate_location);
					break;
					// ゴール
				case 'P':
					object[x][y] = gm->CreateGameObject<Goal>(genelate_location);
					break;
				case 'G':
					object[x][y] = gm->CreateGameObject<Goal>(genelate_location);
					break;
				case 'p':
					object[x][y] = gm->CreateGameObject<Goal>(genelate_location);
					break;
					//ノコノコ
				case 'n':
					object[x][y] = gm->CreateGameObject<Nokonoko>(genelate_location);
					break;
				default:
					break;
				}

				block[x][y] = NULL;
			}

		}
	}
}

/// <summary>
/// オブジェクト削除
/// </summary>
void InGameScene::DeleteStage()
{
	for (int x = 0; x < object.size(); x++)
	{
		for (int y = 0; y < object[x].size(); y++)
		{
			if (object[x][y] != nullptr && object[x][y]->GetLocation().x < camera->GetCameraLocation().x - (D_WIN_MAX_X / 1.9))
			{
				gm->DestroyGameObject(object[x][y]);
				object[x][y] = nullptr;
			}
		}
	}
}
