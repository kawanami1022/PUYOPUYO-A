#include <DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
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


    return std::move(nowScene);
}

UniqueBase GameScene::upDate(UniqueBase nowScene)
{
	for (int i = 0; i < stage.size(); i++)
	{
		stage[i]->SetChainCount(SetChainCount_);
		stage[i]->input();
		SetChainCount_ = stage[i]->update(stage[(i + 1) % stage.size()]->GetStgType());
	}
    return std::move(nowScene);
}

void GameScene::Draw()
{
	ClsDrawScreen();

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer2D();

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer2D();


	stage[0]->draw();
	stage[1]->draw();

	ScreenFlip();
}

void GameScene::DrawInput()
{
}
