#pragma once
#include <memory>
#include "BaseScene.h"
#include "GameScene.h"
class MenuScene:public BaseScene
{
private:
	std::unique_ptr<GameScene> gameScene_;
public:
	MenuScene(std::unique_ptr<GameScene>);
	UniqueBase input(UniqueBase)override;
	UniqueBase upDate(UniqueBase)override;
	void Draw()override;


};

