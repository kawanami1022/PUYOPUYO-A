#include <DxLib.h>
#include <random>
#include "GameScene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "../BLOCK/BLOCK.h"
GameScene::GameScene()
{
	offset = { 50,100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	offset = { 500, 100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));

	BlockNameList_ = { "Image/BLOCK/BLOWNBLOCK.png",
					"Image/BLOCK/BLUEBLOCK.png",
					"Image/BLOCK/GREENASEETS.png",
					"Image/BLOCK/PAPLEBLOCK.png",
					"Image/BLOCK/REDBLOCK.png" };

	for (auto BLOCKLIST : BlockNameList_)
	{
		BlockHandle_.emplace_back(txFcty_.GetTexture(BLOCKLIST));
	}

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
}

GameScene::~GameScene()
{

	stage.clear();
}
UniqueBase GameScene::input(UniqueBase nowScene)
{
	(*comInput)();
	for (auto id : ComInputID())
	{
		if (comInput->push(id))
		{
			{stage[1]->ChangeInputMode(id);}
		}
	}

	if (stage[1]->GetStgType() != STG_TYPE::PLAY)
	{
		if (comInput->push(ComInputID::SPACE))
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

	ScreenFlip();
}

void GameScene::DrawInput()
{
}
