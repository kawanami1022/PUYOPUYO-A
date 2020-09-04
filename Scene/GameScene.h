#pragma once
#include <list>
#include <vector>
#include <string>
#include "BaseScene.h"
#include "../stage.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureFactory.h"
#include "../BLOCK/BLOCK.h"



enum class BLOCK_COLOR;
struct BLOCK;
class TitleScene;

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();
    UniqueBase input(UniqueBase nowScene)override;
    UniqueBase upDate(UniqueBase nowScene)override;
    void Draw()override;
    void DrawInput();       // ì¸óÕèàóùï`âÊä÷êî
private:
    std::vector<std::unique_ptr<Stage>> stage;
    Vector2 offset;
    Vector2 size;
    int SetChainCount_;
    std::vector<BLOCK> Block_;
    int frame_;
    bool InputVisible;

    // Texture

    std::map< ContType, std::function<void(GameScene&)>> TxtureDraw_;
    std::list<std::string> txNmList_;
    std::vector<SharTexture> texture_;
    std::list<std::string> BlockNameList_;
    std::vector<SharTexture> BlockHandle_;
    TextureFactory txFcty_;

    friend struct KEY_INPUT_DRAW;
    friend struct PAD_INPUT_DRAW;
};

