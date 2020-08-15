#include <DxLib.h>

#include "../input/CommonInputID.h"
#include "../input/ComInput.h"
#include "TitleScene.h"
#include "GameScene.h"
TitleScene::TitleScene()
{
	//textureContainer.try_emplace("")
	efkStrList_.emplace_back("Effects/Benediction.efk");
	efkHandle_ = efkFct_.GetEfkHandle(efkStrList_.front(), 1.f);

	PlayingEfk_ = PlayEffekseer2DEffect(efkHandle_->GetHandle());
}

TitleScene::~TitleScene()
{
	efkFct_.EraseEfkHandle("Effects/Benediction.efk");
}

UniqueBase TitleScene::input(UniqueBase nowScene)
{
	(*comInput)();
	if (comInput->push(ComInputID::SPACE))
	{
 		nowScene = std::make_unique<GameScene>();
	}
	SetPosPlayingEffekseer2DEffect(PlayingEfk_, 500, 300, 0);


	return std::move(nowScene);
}

UniqueBase TitleScene::upDate(UniqueBase nowScene)
{
	
	UpdateEffekseer2D();
	return std::move(nowScene);
}

void TitleScene::Draw()
{
	ClsDrawScreen();
	DrawFormatString(0, 0, 0xffffff, "TitleScene");
	DrawEffekseer2D();
	ScreenFlip();
}
