#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

UniqueBase TitleScene::input(UniqueBase&& nowScene)
{
	return std::move(nowScene);
}

UniqueBase TitleScene::upDate(UniqueBase&& nowScene)
{
	return std::move(nowScene);
}

void TitleScene::Draw()
{
}
