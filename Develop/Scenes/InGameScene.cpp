#include "InGameScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "../Objects/GameObjectManager.h"
#include "DxLib.h"
#include <fstream>

InGameScene::InGameScene()
	: player(nullptr)
	, back_ground_stage(NULL)
	, ground_stage(NULL)
	, back_bgm(NULL)
	, pause_flag(false)
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
	std::vector<int>initi_back(15, back_ground_stage);
	haikei_block = std::vector<std::vector<int>>(211, initi_back);

	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	GameObjectManager* gm = GameObjectManager::GetInstance();

	player = gm->CreateGameObject<Player>(Vector2D(100, 300));

	// マップデータ読み込み生成処理
	LoadBackStageMapCSV();
	LoadStageMapCSV();

	// BGMの読み込み
	back_bgm = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_bgm, DX_PLAYTYPE_BACK);
}

eSceneType InGameScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::GetInstance();
	camera->CameraUpdate(player->GetLocation());		//プレイヤーの座標を基にカメラを更新

	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}

	if (!pause_flag)
	{
		// 親クラスの更新処理を呼び出す
		__super::Update(delta_second);
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

	LoadStageMapCSV();

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
void InGameScene::CheckCollision(GameObjectManager* target, GameObjectManager* partner)
{
	
}

/// <summary>
/// ステージマップ（ブロック）読み込み処理
/// </summary>
void InGameScene::LoadStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Book.csv";

	ResourceManager* rm = ResourceManager::GetInstance();

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
			// 床
			case 'f':
				ground_stage = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];
				break;
			// 階段ブロック
			case 'B':
				ground_stage = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32)[0];
				break;
			// ブロック
			case 'b':
				ground_stage = rm->GetImages("Resource/Images/Block/block.png", 1, 1, 1, 32, 32)[0];
				break;
			// ？ブロック
			case 'h':
				ground_stage = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32)[0];
				break;
			//土管
			case 'd':
				ground_stage = rm->GetImages("Resource/Images/dokan_left_up.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'o':
				ground_stage = rm->GetImages("Resource/Images/dokan_right_up.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'A':
				ground_stage = rm->GetImages("Resource/Images/dokan_left_down.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'K':
				ground_stage = rm->GetImages("Resource/Images/dokan_right_down.png", 1, 1, 1, 32, 32)[0];
				break;
			// クリボー
			case 'k':
				ground_stage = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];
				break;
			// ゴール
			case 'P':
				ground_stage = rm->GetImages("Resource/Images/pole.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'G':
				ground_stage = rm->GetImages("Resource/Images/pole_down.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'p':
				ground_stage = rm->GetImages("Resource/Images/pole_down.png", 1, 1, 1, 32, 32)[0];
				break;
			default:
				break;
			}

			// 生成(仮)
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

	ResourceManager* rm = ResourceManager::GetInstance();

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
		else if(c != ' ' && c != '\n' && c!= ',')
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
