#include <DxLib.h>
#include "SceneMng.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "EfkMng/EfkMng.h"
#include "input/controller.h"
SceneMng* SceneMng::hInstance = nullptr;

int SceneMng::Run()
{

	ChangeWindowMode(true);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	SetUseDirect3DVersion(DX_SCREEN_BACK);
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	lpEfkMng;
	nowScene = std::make_unique<TitleScene>();

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	// ���[�v
	while (ProcessMessage() == 0)
	{
		nowScene = nowScene->input(std::move(nowScene));
		nowScene = nowScene->upDate(std::move(nowScene));
		nowScene->Draw();
	}

	lpEfkMng.Destroy();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;
}

SceneMng::SceneMng()
{
	offset = {0,0};
	size = { 400,600 };
	SetChainCount_ = 0;
}

SceneMng::~SceneMng()
{
}



