#include <EffekseerForDXLib.h>
#include "EffekseerFactory.h"

SharEfk EffekseerFactory::GetEfkHandle(std::string FileName, float mag)
{
    auto it = EfkContainer_.find(FileName);
    if (it != EfkContainer_.end())    //Œ©‚Â‚©‚Á‚½
    {
        return EfkContainer_[FileName];
    }
    EfkContainer_.try_emplace(FileName, CreateEfkHandle(FileName, mag));
    return EfkContainer_[FileName];
}

void EffekseerFactory::EraseEfkHandle(std::string FileName)
{
    DeleteEffekseerEffect(EfkContainer_[FileName]->GetHandle());
    EfkContainer_.erase(FileName);
}

SharEfk EffekseerFactory::CreateEfkHandle(std::string FileName, float mag)
{
    SharEfk EfkHandle_ =
        std::make_unique<Effect>(LoadEffekseerEffect(FileName.data(), mag), mag);
    return EfkHandle_;
}
