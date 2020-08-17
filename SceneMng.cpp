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
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	lpEfkMng;
	nowScene = std::make_unique<TitleScene>();

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// ループ
	while (ProcessMessage() == 0)
	{
		nowScene = nowScene->input(std::move(nowScene));
		nowScene = nowScene->upDate(std::move(nowScene));
		nowScene->Draw();
	}

	lpEfkMng.Destroy();
	DxLib_End();				// ＤＸライブラリ使用の終了処理
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



