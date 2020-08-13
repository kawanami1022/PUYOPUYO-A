#include <DxLib.h>
#include "ComInput.h"

bool ComInput::Setup()
{
    _ComInputTbl.try_emplace(ComInputID::PG_UP, KEY_INPUT_PGUP);
    _ComInputTbl.try_emplace(ComInputID::PG_DOWN, KEY_INPUT_PGDN);
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
}

bool ComInput::push(ComInputID comInputID)
{
    return (comData_[comInputID][static_cast<int>(Trg::Now)] == 1
            &&comData_[comInputID][static_cast<int>(Trg::Old)]==0);
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
