#include <DxLib.h>
#include "SceneMng.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	lpSceneMng.Run();
	lpSceneMng.Destroy();
	return 0;
}
