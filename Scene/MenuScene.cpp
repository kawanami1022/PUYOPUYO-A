#include <DxLib.h>
#include "MenuScene.h"

MenuScene::MenuScene(UniqueBase& gameScene)
{
	gameScene_ = std::move(gameScene);
}

UniqueBase MenuScene::input(UniqueBase nowScene)
{
	(*comInput)();
	if (comInput->push(ComInputID::F1))
	{
		nowScene = std::move(gameScene_);
		SetDrawBright(255, 255, 255);

	}
	return nowScene;
}

UniqueBase MenuScene::upDate(UniqueBase nowScene)
{
	return nowScene;
}

void MenuScene::Draw()
{
	ClsDrawScreen();
	DrawFormatString(0, 0, 0xffffff, "MenueScene");
	SetDrawBright(200, 200, 200);
	gameScene_->Draw();
	ScreenFlip();
}
