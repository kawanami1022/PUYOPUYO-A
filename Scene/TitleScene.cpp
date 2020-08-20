#include <DxLib.h>

#include "../input/CommonInputID.h"
#include "../input/ComInput.h"
#include "TitleScene.h"
#include "GameScene.h"

#define STCI static_cast<int>
TitleScene::TitleScene()
{
	frame_ = 0;
	texture_.emplace_back(txFcty_.GetTexture("Image/スペースキー押して.png"));
}

TitleScene::~TitleScene()
{
}

UniqueBase TitleScene::input(UniqueBase nowScene)
{
	(*comInput)();
	if (comInput->push(ComInputID::SPACE)==true)
	{
 		nowScene = std::make_unique<GameScene>();
	}
	frame_++;

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
	if (frame_ % 60 > 30)
	{ 
		DrawGraph(400 - texture_[STCI(TxNameID::PUSH_SPC)]->GetSize().x / 2,
			500 - texture_[STCI(TxNameID::PUSH_SPC)]->GetSize().y / 2,
			texture_[STCI(TxNameID::PUSH_SPC)]->GetHandle(), true);
	}
	ScreenFlip();
}
