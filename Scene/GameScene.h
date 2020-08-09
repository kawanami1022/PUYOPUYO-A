#pragma once
#include <vector>
#include "BaseScene.h"
#include "../stage.h"
#include "../Texture/TextureFactory.h"
#include "../Texture/Texture.h"

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();
    UniqueBase input(UniqueBase nowScene)override;
    UniqueBase upDate(UniqueBase nowScene)override;
    void Draw()override;
private:
    std::vector<std::unique_ptr<Stage>> stage;
    Vector2 offset;
    Vector2 size;
    int SetChainCount_;
    std::vector<SharTexture> texture;
};

