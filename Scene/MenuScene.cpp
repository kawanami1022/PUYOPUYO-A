#include <DxLib.h>
#include "MenuScene.h"

MenuScene::MenuScene(std::unique_ptr<GameScene> gameScene)
{
	gameScene_ = std::move(gameScene);
}

UniqueBase MenuScene::input(UniqueBase nowScene)
{
	return nowScene;
}

UniqueBase MenuScene::upDate(UniqueBase nowScene)
{
	return nowScene;
}

void MenuScene::Draw()
{

	SetDrawBright(255, 255, 255);
	DrawFormatString(0, 0, 0xffffff, "MenueScene");
	SetDrawBright(200, 200, 200);
}
