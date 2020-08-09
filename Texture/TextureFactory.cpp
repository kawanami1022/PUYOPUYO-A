#include <DxLib.h>
#include "TextureFactory.h"

SharTexture TextureFactory::GetTexture(std::string FileName)
{
    auto it = TextureContainer_.find(FileName);
    if (it != TextureContainer_.end())
    {return TextureContainer_[FileName];}

    TextureContainer_.insert(
        std::make_pair(FileName, CreateTexture(FileName)));

    return TextureContainer_[FileName];
}

SharTexture TextureFactory::CreateTexture(std::string FileName)
{
    SharTexture texture = std::make_unique<Texture>(FileName);
    return texture;
}
