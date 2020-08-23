#pragma once
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
    std::list<std::string> txNmList_;
    int frame_;
    TextureFactory txFcty_;
    std::vector<SharTexture> texture_;
};

