#pragma once
#include "BaseScene.h"
#include "../stage.h"

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();
    UniqueBase input(UniqueBase&& nowScene)override;
    UniqueBase upDate(UniqueBase&& nowScene)override;
    void Draw()override;
private:
    std::vector<std::unique_ptr<Stage>> stage;
    Vector2 offset;
    Vector2 size;
    int SetChainCount_;
};

