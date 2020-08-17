#include <DxLib.h>
#include "ComInput.h"
ComData ComInput::comData_;

bool ComInput::Setup()
{
    _ComInputTbl.try_emplace(ComInputID::PG_UP, KEY_INPUT_PGUP);
    _ComInputTbl.try_emplace(ComInputID::PG_DOWN, KEY_INPUT_PGDN);
    _ComInputTbl.try_emplace(ComInputID::SPACE, KEY_INPUT_SPACE);
    frame_ = 0;
    return true;
}

bool ComInput::reset()
{
    for (auto id : ComInputID())
    {
        comData_[id][static_cast<int>(Trg::Old)] = 0;
        comData_[id][static_cast<int>(Trg::Now)] = 0;
    }
    return false;
}

void ComInput::Update(void)
{
    GetHitKeyStateAll(_ComkeyData.data());
    for (auto id:ComInputID())
    {
        comData_[id][static_cast<int>(Trg::Old)] = comData_[id][static_cast<int>(Trg::Now)];
        comData_[id][static_cast<int>(Trg::Now)] = _ComkeyData[_ComInputTbl[id]];
    }
    frame_++;
 }

bool ComInput::push(ComInputID comInputID)
{
    if (comData_[comInputID][static_cast<int>(Trg::Now)] == 1
        && comData_[comInputID][static_cast<int>(Trg::Old)] == 0)
    {
        return true;
    }
    return false;
}

bool ComInput::Hold(ComInputID comInputID)
{
    return (comData_[comInputID][static_cast<int>(Trg::Now)] == 1
        && comData_[comInputID][static_cast<int>(Trg::Old)] == 1);
}

bool ComInput::release(ComInputID comInputID)
{
    return (comData_[comInputID][static_cast<int>(Trg::Now)] == 0
        && comData_[comInputID][static_cast<int>(Trg::Old)] == 1);
}

bool ComInput::separate(ComInputID comInputID)
{
    return (comData_[comInputID][static_cast<int>(Trg::Now)] == 0
        && comData_[comInputID][static_cast<int>(Trg::Old)] == 0);
}

ComData ComInput::GetComData()
{
    return comData_;
}
