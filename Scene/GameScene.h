#pragma once
#include <list>
#include <vector>
#include <string>
#include "BaseScene.h"
#include "../stage.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureFactory.h"



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

    // Texture
    std::list<std::string> BlockNameList_;
    std::vector<SharTexture> BlockHandle_;
    TextureFactory txFcty_;
};

