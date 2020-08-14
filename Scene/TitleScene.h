#pragma once
#include <EffekseerForDXLib.h>
#include "BaseScene.h"
class TitleScene :
    public BaseScene
{
public:
    TitleScene();
    ~TitleScene();
    UniqueBase input(UniqueBase nowScene)override;
    UniqueBase upDate(UniqueBase nowScene)override;
    void Draw()override;
};

