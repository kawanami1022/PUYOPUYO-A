#pragma once
#include <memory>
#include "BaseScene.h"
#include "GameScene.h"
class MenuScene:public BaseScene
{
private:
	UniqueBase gameScene_;
public:
	MenuScene(UniqueBase & gameScene);
	UniqueBase input(UniqueBase)override;
	UniqueBase upDate(UniqueBase)override;
	void Draw()override;


};

