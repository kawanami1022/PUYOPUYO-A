#pragma once
#include <string>
#include <EffekseerForDXLib.h>
#include "BaseScene.h"
#include "../Effekseer/EffekseerFactory.h"

class TitleScene :
    public BaseScene
{
public:
    TitleScene();
    ~TitleScene();
    UniqueBase input(UniqueBase nowScene)override;
    UniqueBase upDate(UniqueBase nowScene)override;
    void Draw()override;
private:
    EffekseerFactory efkFct_;   
    SharEfk efkHandle_;
    std::list<std::string> efkStrList_;
    int PlayingEfk_;
};

