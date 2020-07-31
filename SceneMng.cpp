#include <DxLib.h>
#include "SceneMng.h"
#include "stage.h"

SceneMng* SceneMng::hInstance = nullptr;

int SceneMng::Run()
{

	ChangeWindowMode(true);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}
	offset = { 100,100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	offset = { 500, 100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	handle = MakeScreen(240, 400, false);
	SetDrawScreen(handle);
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	// ���[�v
	while (ProcessMessage() == 0)
	{
		stage[0]->input();
		stage[1]->input();
		stage[0]->update();
		stage[1]->update();
		draw();
	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;
}

SceneMng::SceneMng()
{
	offset = {0,0};
	size = { 400,600 };

}

SceneMng::~SceneMng()
{
}

void SceneMng::draw()
{
	ClsDrawScreen();

	stage[0]->draw();
	stage[1]->draw();
	ScreenFlip();

}

