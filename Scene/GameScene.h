#pragma once
#include <vector>
#include "BaseScene.h"
#include "../stage.h"

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();
    UniqueBase input(UniqueBase nowScene)override;
    UniqueBase upDate(UniqueBase nowScene)override;
    void Draw()override;
    void DrawInput();       // “ü—Íˆ—•`‰æŠÖ”
private:
    std::vector<std::unique_ptr<Stage>> stage;
    Vector2 offset;
    Vector2 size;
    int SetChainCount_;
};

