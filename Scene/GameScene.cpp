#include <DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
GameScene::GameScene()
{
	offset = { 50,100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));
	offset = { 500, 100 };
	stage.emplace_back(new Stage(std::move(offset), std::move(size)));

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

	stage[0]->draw();
	stage[1]->draw();

	ScreenFlip();
}

void GameScene::DrawInput()
{
}
