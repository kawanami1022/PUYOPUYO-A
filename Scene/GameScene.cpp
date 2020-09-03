#include <DxLib.h>
#include <random>
#include "GameScene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "../BLOCK/BLOCK.h"
#include "GAME_INPUT_DRAW/KEY_INPUT_DRAW.h"
#include "GAME_INPUT_DRAW/PAD_INPUT_DRAW.h"

GameScene::GameScene()
{
	offset = { 50,100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	offset = { 500, 100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	frame_ = 0;
	BlockNameList_ = { "Image/BLOCK/BLOWNBLOCK.png",
					"Image/BLOCK/BLUEBLOCK.png",
					"Image/BLOCK/GREENASEETS.png",
					"Image/BLOCK/PAPLEBLOCK.png",
					"Image/BLOCK/REDBLOCK.png" };

	for (auto BLOCKLIST : BlockNameList_)
	{
		BlockHandle_.emplace_back(txFcty_.GetTexture(BLOCKLIST));
	}

	txNmList_ = { "Image/スペースキー押して.png","Image/A_BUTTON.png","Image/titleLogo.png" };
	for (auto&& TXNMList : txNmList_)
	{
		texture_.emplace_back(txFcty_.GetTexture(TXNMList));
	}
	TxtureDraw_.try_emplace(ContType::Key, KEY_INPUT_DRAW());
	TxtureDraw_.try_emplace(ContType::Pad, PAD_INPUT_DRAW());
	const int width = 14;
	const int height = 14;


	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution<> dist1(static_cast<int>(BLOCK_COLOR::BLOWN), static_cast<int>(BLOCK_COLOR::RED));

	Block_.reserve(width * height);
	for (int i = 0; i < width * height; i++)
	{
		int color = dist1(engine);
		Vector2 size = BlockHandle_[color]->GetSize();

		Block_.emplace_back(
			BLOCK({ size.x * (i % width) - size.x / 2 + (i / width % 2 * size.x / 2),
			(i/width)*(size.y-size.y/4)-size.y/2 },
				size, BlockHandle_[color]->GetHandle()));
	}
	if (controller->GetType() == ContType::Key)
		controller->changeInputTbl(KEY_INPUT_SPACE, InputID::TURN_L);
}

GameScene::~GameScene()
{

	stage.clear();
}
UniqueBase GameScene::input(UniqueBase nowScene)
{
	(*comInput)();
	(*controller)();
	for (auto id : ComInputID())
	{
		if (comInput->push(id))
		{
			{stage[1]->ChangeInputMode(id);}
		}
	}

	if (stage[1]->GetStgType() != STG_TYPE::PLAY)
	{
		if (controller->push(InputID::TURN_L))
		{
			nowScene = std::make_unique<TitleScene>();
		}
	}
	if (comInput->push(ComInputID::F1))
	{
		nowScene = std::make_unique<MenuScene>(nowScene);
	}

    return std::move(nowScene);
}

UniqueBase GameScene::upDate(UniqueBase nowScene)
{
	for (int i = 0; i < stage.size(); i++)
	{
		stage[i]->SetChainCount(SetChainCount_);
		stage[i]->input();
		SetChainCount_ = stage[i]->update(stage[(STCI(i + 1)) % stage.size()]->GetStgType());
	}
	frame_++;
    return std::move(nowScene);
}

void GameScene::Draw()
{
	ClsDrawScreen();
	for (auto BLOCK : Block_)
	{
		DrawGraph(BLOCK.pos_.x, BLOCK.pos_.y, BLOCK.GrHdl_, true);
	}

	stage[0]->draw();
	stage[1]->draw();

	if (stage[0]->GetStgType()!=STG_TYPE::PLAY)
	{
		TxtureDraw_[controller->GetType()](*this);
	}
	ScreenFlip();
}

void GameScene::DrawInput()
{
}
