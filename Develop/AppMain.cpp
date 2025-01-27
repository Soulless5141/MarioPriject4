#include "DxLib.h"
#include "Scenes/SceneManager.h"
#include "Utility/Application.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	try
	{
		Application app ;

		app.WakeUp();

		app.Run();

		app.Shutdown();
	}
	catch (std::string error_log)
	{
		// エラー内容を出力する
		return ErrorThrow(error_log);
	}

	DxLib_End();

	return 0;

}