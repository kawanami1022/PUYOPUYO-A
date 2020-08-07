#include <DxLib.h>
#include "SceneMng.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
SceneMng* SceneMng::hInstance = nullptr;

int SceneMng::Run()
{

	ChangeWindowMode(true);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// ループ
	while (ProcessMessage() == 0)
	{
		nowScene = nowScene->input(std::move(nowScene));
		nowScene = nowScene->upDate(std::move(nowScene));
		nowScene->Draw();
	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;
}

SceneMng::SceneMng()
{
	offset = {0,0};
	size = { 400,600 };
	SetChainCount_ = 0;
	nowScene = std::make_unique<GameScene>();
}

SceneMng::~SceneMng()
{
}



