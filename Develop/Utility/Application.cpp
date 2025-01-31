#include "Application.h"
#include "DxLib.h"



Application::Application()
{

}

Application::~Application()
{
	Shutdown();
}

// �O���[�o���ϐ���`
LONGLONG old_time;		// �O��v���l
LONGLONG now_time;		// ���݌v���l
float delta_second;		// �P�t���[��������̎���

// �t���[�����Ԍv��
void FreamControl()
{
	// ���ݎ��Ԃ̎擾�i�ʕb�j
	now_time = GetNowHiPerformanceCount();

	// �J�n���Ԃ��猻�ݎ��Ԃ܂łɌo�߂������Ԃ��v�Z����i�ʕb�j
	// ����\���ʕb���b�ɕϊ�����
	delta_second = (float)(now_time - old_time) * 1.0e-6f;

	// �v���J�n���Ԃ��X�V����
	old_time = now_time;

	// �f�B�X�v���C�̃��t���b�V�����[�g���擾����
	float refresh_rate = (float)GetRefreshRate();

	// �P�t���[��������̎��Ԃ�1/���t���b�V�����[�g�b�𒴂�����A������
 	if (delta_second > (1.0f / refresh_rate))
	{
		delta_second = (1.0f / refresh_rate);
	}

}

// 1�t���[��������̎��Ԃ��擾����
const float& GetDeltaSecond()
{
	return delta_second;
}

// �G���[���e���o�͂���
int ErrorThrow(std::string error_log)
{
	// Log.txt�ɃG���[���e��ǉ�����
	ErrorLogFmtAdd(error_log.c_str());
	return D_FAILURE;
}

void Application::WakeUp()
{
	// �E�B���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// �E�B���h�E�^�C�g���̐ݒ�
	SetWindowText("SuperMario.exe");

	// �����������s��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// Log.txt�t�@�C���̐�������iDebug���[�h�̂ݐ�������j
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dx���C�u�����̏�����
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dx���C�u�����̏������Ɏ��s���܂����I\n");
	}

	// �`����\��ʂɔ��f����
	SetDrawScreen(DX_SCREEN_BACK);

	scene->Initialize();

	// ��A�N�e�B�u��Ԃł����삳����
	SetAlwaysRunFlag(TRUE);
}

void Application::Run()
{
	// ���͏����擾����
	input = InputManager::Get();

	// ���C�����[�v
	while (ProcessMessage() == D_SUCCESS)
	{
		// ���͏��̍X�V
		input->Update();

		// �t���[�����[�g�̐���
		FreamControl();

		scene->Update(delta_second);

		// �Q�[�����I�����邩�m�F����
		if (/*(next_scene_type == eSceneType::exit) ||*/
			(input->GetButtonUp(XINPUT_BUTTON_BACK)) ||
			(input->GetKeyUp(KEY_INPUT_ESCAPE)))
		{
			break;
		}
	}
}

void Application::Shutdown()
{
	//scene->Finalize();

	// Singleton�̃C���X�^���X���������
	input->DeleteInstance(input);
	rm->DeleteInstance(rm);

	// Dx���C�u�����̎g�p���I������
	DxLib_End();
}

void Application::UpdateDeltaTime()
{
	
}