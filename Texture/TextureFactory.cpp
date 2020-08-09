#include <DxLib.h>
#include "TextureFactory.h"

SharTexture TextureFactory::GetTexture(std::string FileName)
{
    auto it = TextureContainer_.find(FileName);
    if (it != TextureContainer_.end())
    {return it->second;}
    auto newTexture = CreateTexture(FileName);
    TextureContainer_.insert(TextureContainer_.begin(),
        std::make_pair(FileName, newTexture));

    return TextureContainer_[FileName];
}

SharTexture TextureFactory::CreateTexture(std::string FileName)
{
    SharTexture texture;
    auto GrHandle = LoadGraph(FileName.data(), 0);
        texture = std::make_unique<Texture>(GrHandle);

    return texture;
}
