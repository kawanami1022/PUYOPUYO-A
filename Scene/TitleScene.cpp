#include <DxLib.h>
#include "../DxLibForHomeBrew/DxLib_Draw.h"
#include "../input/CommonInputID.h"
#include "../input/ComInput.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "TITLE_INPUT_DRAW/KEY_INPUT_DRAW.h"
#include "TITLE_INPUT_DRAW/PAD_INPUT_DRAW.h"
#define STCI static_cast<int>
TitleScene::TitleScene()
{
	frame_ = 0;
	
	txNmList_ = { "Image/スペースキー押して.png","Image/A_BUTTON.png","Image/titleLogo.png" };
	for (auto&& TXNMList : txNmList_)
	{texture_.emplace_back(txFcty_.GetTexture(TXNMList));}
	TxtureDraw_.try_emplace(ContType::Key, KEY_INPUT_DRAW());
	TxtureDraw_.try_emplace(ContType::Pad, PAD_INPUT_DRAW());
	//
	if (controller->GetType() == ContType::Key)
		controller->changeInputTbl(KEY_INPUT_SPACE, InputID::TURN_L);
}

TitleScene::~TitleScene()
{
}

UniqueBase TitleScene::input(UniqueBase nowScene)
{
	(*controller)();
	controller->AutoChangeInput(controller, 0);
	if (controller->push(InputID::TURN_L) == true)
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
	int offSize = frame_ % 30;
	DxLib_Draw::DrawExtendGraphCe(400, 150, texture_[2]->GetSize().x, texture_[2]->GetSize().y - offSize, texture_[2]->GetHandle());
	TxtureDraw_[controller->GetType()](*this);
	ScreenFlip();
}
