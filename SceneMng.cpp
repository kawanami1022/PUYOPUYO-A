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
	offset = { 50,100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	offset = { 500, 100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// ループ
	while (ProcessMessage() == 0)
	{
		upDate();
		draw();
	}


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

void SceneMng::upDate()
{
	for (int i = 0; i < stage.size(); i++)
	{
		stage[i]->SetChainCount(SetChainCount_);
		stage[i]->input();
		SetChainCount_=stage[i]->update();
	}
}

void SceneMng::draw()
{
	ClsDrawScreen();

	stage[0]->draw();
	stage[1]->draw();
	ScreenFlip();

}

