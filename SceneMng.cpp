#include <DxLib.h>
#include "SceneMng.h"
#include "stage.h"

SceneMng* SceneMng::hInstance = nullptr;

int SceneMng::Run()
{

	ChangeWindowMode(true);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}
	offset = { 100,100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	offset = { 500, 100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	handle = MakeScreen(240, 400, false);
	SetDrawScreen(handle);
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// ループ
	while (ProcessMessage() == 0)
	{
		stage[0]->input();
		stage[1]->input();
		stage[0]->update();
		stage[1]->update();
		draw();
	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理
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

