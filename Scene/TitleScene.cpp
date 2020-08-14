#include <DxLib.h>

#include "../input/CommonInputID.h"
#include "../input/ComInput.h"
#include "TitleScene.h"
#include "GameScene.h"
TitleScene::TitleScene()
{
	//textureContainer.try_emplace("")
}

TitleScene::~TitleScene()
{
}

UniqueBase TitleScene::input(UniqueBase nowScene)
{
	(*comInput)();
	if (comInput->push(ComInputID::SPACE))
	{
 		nowScene = std::make_unique<GameScene>();
	}
	return std::move(nowScene);
}

UniqueBase TitleScene::upDate(UniqueBase nowScene)
{
	return std::move(nowScene);
}

void TitleScene::Draw()
{
	ClsDrawScreen();
	DrawFormatString(0, 0, 0xffffff, "TitleScene");
	ScreenFlip();
}
