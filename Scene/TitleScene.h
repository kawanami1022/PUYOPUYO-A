#pragma once
#include <functional>
#include <vector>
#include <string>
#include <list>
#include <EffekseerForDXLib.h>
#include "BaseScene.h"
#include "../Texture/TextureFactory.h"
#include "../Texture/Texture.h"

enum class TxNameID
{
    PUSH_SPC,
    MAX,
};

class TitleScene :public BaseScene
{
public:
    TitleScene();
    ~TitleScene();
    UniqueBase input(UniqueBase nowScene)override;
    UniqueBase upDate(UniqueBase nowScene)override;
    void Draw()override;
private:
    int frame_;
    TextureFactory txFcty_;
    std::list<std::string> txNmList_;
    std::vector<SharTexture> texture_;
    std::map< ContType,std::function<void(TitleScene&)>> TxtureDraw_;
    friend struct KEY_INPUT_DRAW;
    friend struct PAD_INPUT_DRAW;
};

