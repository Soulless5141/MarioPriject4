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
	// �X�N���[���I�t�Z�b�g��ݒ�
	camera = Camera::Get();

	//�z�񏉊���
	std::vector<int>initi_back(BLOCK_MAX_Y, back_ground_stage);
	haikei_block = std::vector<std::vector<int>>(BLOCK_MAX_X, initi_back);
	std::vector<int>initi_ground(BLOCK_MAX_Y, ground_stage);
	block = std::vector<std::vector<int>>(BLOCK_MAX_X, initi_ground);
	std::vector<GameObject*>initi_object(BLOCK_MAX_Y, nullptr);
	object = std::vector<std::vector<GameObject*>>(BLOCK_MAX_X, initi_object);

	// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::Get();
	GameObjectManager* gm = GameObjectManager::Get();

	ui_time = rm->GetImages("Resource/Images/UI/time.png")[0];

	ui_world = rm->GetImages("Resource/Images/UI/world.png")[0];

	ui_coin_1_score = rm->GetImages("Resource/Images/UI/uicoin_1.png")[0];

	ui_mario_score = rm->GetImages("Resource/Images/UI/name_mario.png")[0];

	player = gm->CreateGameObject<Player>(Vector2D(100, 384));

	gm->CreateGameObject<Kinoko>(Vector2D(200, 250));

	// �}�b�v�f�[�^�ǂݍ��ݐ�������
	LoadBackStageMapCSV();
	LoadStageMapCSV();

	// BGM�̓ǂݍ���
	back_bgm = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	//PlaySoundMem(back_bgm, DX_PLAYTYPE_BACK);
	__super::Initialize();
}

eSceneType InGameScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::Get();
	camera->CameraUpdate(player->GetLocation());		//�v���C���[�̍��W����ɃJ�������X�V

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
		// �e�N���X�̍X�V�������Ăяo��
		__super::Update(delta_second);

		DeleteStage();
	}

	// �V�[������ԋp����
	return GetNowSceneType();
}

void InGameScene::Draw()
{
	// �w�i�摜�̕`��
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


	// �f�o�b�O�p�g������������
	/*DrawBoxAA(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, 0xff0000, false);
	DrawFormatString(10,0, 0x000000, "%f", camera->GetCameraLocation().x);*/

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	// UI�n�̕`�揈��
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
void InGameScene::CheckCollision(GameObject* target, GameObject* partner)
{
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		// �J�v�Z�����m�̓����蔻��
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
		//	// �������Ă��邱�Ƃ�ʒm����
		//	partner->OnHitCollision(target);
		//	target->OnHitCollision(partner);

		//}
	}
}

/// <summary>
/// �X�e�[�W�}�b�v�i�u���b�N�j�ǂݍ��ݏ���
/// </summary>
void InGameScene::LoadStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Book.csv";

	ResourceManager* rm = ResourceManager::Get();

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// �����𒊏o���Ċi�[
		else if (c != ' ' && c != '\n' && c != ',')
		{

			switch (c)
			{
				// ��
			case 'f':
				ground_stage = 'f';
				break;
				// �K�i�u���b�N
			case 'B':
				ground_stage = 'B';
				break;
				// �u���b�N
			case 'b':
				ground_stage = 'b';
				break;
				// �H�u���b�N
			case 'h':
				ground_stage = 'h';
				break;
				//�y��
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
				// �N���{�[
			case 'k':
				ground_stage = 'k';
				break;
				// �S�[��
			case 'P':
				ground_stage = 'P';
				break;
			case 'G':
				ground_stage = 'G';
				break;
			case 'p':
				ground_stage = 'p';
				break;
				//�m�R�m�R
			case 'n':
				ground_stage = 'n';
				break;
			default:
				break;
			}
			// �i�[
			block[x][y] = ground_stage;
			x++;
		}

		// ���o�����������󔒕����Ȃ�A�������Ȃ��Ŏ��̕��������ɍs��
		else if (c == ' ')
		{
			ground_stage = NULL;
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}
	// �J�����t�@�C�������
	fclose(fp);
}

/*<summary>
�X�e�[�W�}�b�v�ǂݍ��ݏ���
</summary>*/
void InGameScene::LoadBackStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Haikei.csv";

	ResourceManager* rm = ResourceManager::Get();

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// �����𒊏o���Ċi�[
		else if (c != ' ' && c != '\n' && c != ',')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);

			switch (c)
			{
				//��̓ǂݍ���
			case 's':
				back_ground_stage = rm->GetImages("Resource/Images/sora.png", 1, 1, 1, 32, 32)[0];
				break;
				// �_�̓ǂݍ���
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

				// �R�̓ǂݍ���
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
				// ���̓ǂݍ���
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

			// �z��Ɋi�[
			haikei_block[x][y] = back_ground_stage;
			x++;
		}

		// ���o�����������󔒕����Ȃ�A�������Ȃ��Ŏ��̕��������ɍs��
		else if (c == ' ')
		{
			back_ground_stage = NULL;
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}
	// �J�����t�@�C�������
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
					// ��
				case 'f':
					object[x][y] = gm->CreateGameObject<Ground>(genelate_location);
					break;
					// �K�i�u���b�N
				case 'B':
					object[x][y] = gm->CreateGameObject<Stairs>(genelate_location);
					break;
					// �u���b�N
				case 'b':
					object[x][y] = gm->CreateGameObject<Block>(genelate_location);
					break;
					// �H�u���b�N
				case 'h':
					object[x][y] = gm->CreateGameObject<Hatena>(genelate_location);
					break;
					//�y��
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
					// �N���{�[
				case 'k':
					object[x][y] = gm->CreateGameObject<kuribo>(genelate_location);
					break;
					// �S�[��
				case 'P':
					object[x][y] = gm->CreateGameObject<Goal>(genelate_location);
					break;
				case 'G':
					object[x][y] = gm->CreateGameObject<Goal>(genelate_location);
					break;
				case 'p':
					object[x][y] = gm->CreateGameObject<Goal>(genelate_location);
					break;
					//�m�R�m�R
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
/// �I�u�W�F�N�g�폜
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
